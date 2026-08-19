#include "LCD.h"

bool lcd_init(struct lcdinfo *p, const char * path_name)
{
    p->fd = open(path_name, O_RDWR);
    if(p->fd == -1)
    {
        perror("open lcd failed");
        return false;
    }
    
    struct fb_var_screeninfo info;
    ioctl(p->fd, FBIOGET_VSCREENINFO, &info);
    p->w = info.xres;
    p->h = info.yres;
    p->bpp = info.bits_per_pixel;
    p->pitch = p->w * p->bpp /8;
    p->size = p->pitch * p->h;

    p->map = mmap(NULL, p->size, PROT_WRITE | PROT_READ,
                        MAP_SHARED, p->fd, 0);
    if(p->map == MAP_FAILED)
    {
        perror("mmap lcd failed");
        return false;
    }

    memset(p->map, 0xFFFFFF, p->size);

    return true;
}

void lcd_release(struct lcdinfo *p)
{
    if(p == NULL)
        return;
    
    munmap(p->map, p->size);
    close(p->fd);
}
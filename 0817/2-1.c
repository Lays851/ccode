#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/input.h> 
#include <time.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <string.h>
#include <linux/fb.h>

int main (void)
{
    int fd = open ("/dev/input/event6", O_RDONLY);
    if(fd == -1)
    {
        perror("open touch_panel failed");
        exit(1);
    }

    int lcd = open ("/dev/fb0", O_RDWR);
    if(lcd == -1)
    {
        perror("open lcd failed");
        exit(1);
    }

    struct fb_var_screeninfo vinfo;
    ioctl(lcd, FBIOGET_VSCREENINFO, &vinfo);
    int lcd_w = vinfo.xres;
    int lcd_h = vinfo.yres;
    int lcd_bpp = vinfo.bits_per_pixel;
    int lcd_size = lcd_w * lcd_h * lcd_bpp / 8;

    char *p = mmap(NULL, lcd_size, PROT_READ | PROT_WRITE , MAP_SHARED, lcd , 0);
    if(p == MAP_FAILED)
    {
        perror("mmap failed");
        exit(1);
    }

    struct input_event ev;
    while(1)
    {
        bzero(&ev, sizeof(ev));
        read(fd, &ev, sizeof(ev));

        srand(time(NULL));
        int num = rand() % 0x1000000;
        printf("%#x\n", num);
        if(ev.type == EV_KEY && ev.code == BTN_TOUCH)
        {
            if(ev.value == 1)
            {
                for(int j = 0 ; j < lcd_h ; j++)
                {
                    int lcd_off = lcd_w * lcd_bpp / 8 * j; 
                    for(int i = 0; i < lcd_w; i++)
                    {
                       memcpy(p + (4 * i) + lcd_off, &num, lcd_bpp / 8);   
                    }
                }
            }
        }
    }

    return 0;
}
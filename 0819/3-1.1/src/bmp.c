#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

#include "image.h"
#include "LCD.h"

// 显示指定的一张bmp格式的图片
void imageshow(struct lcdinfo *lcd, char const *filename) // ./a.out xxx.bmp
{
    if(filename == NULL)
        return;
    
    struct fb_var_screeninfo vinfo;
    ioctl(lcd->fd, FBIOGET_VSCREENINFO, &vinfo);

    int lcd_w = vinfo.xres;
    int lcd_h = vinfo.yres;
    int lcd_bpp = vinfo.bits_per_pixel;
    int lcd_line_size = lcd_w * lcd_bpp / 8;
    int lcd_size = lcd_w * lcd_h * lcd_bpp / 8;

    int fd = open(filename, O_RDONLY);
    if(fd == -1)
    {
        perror("open bmp failed");
        return;
    }

    // 读取bmp文件RGB数据
    struct bitmap_header header;
    struct bitmap_info   info;
    bzero(&header, sizeof(header));
    bzero(&info, sizeof(info));

    read(fd, &header, sizeof(header));
    read(fd, &info, sizeof(info));

    if(info.compression != 0)
    {
        struct rgb_quad quad;
        bzero(&quad, sizeof(quad));
        read(fd, &quad, sizeof(quad));
    }

    int bmp_w = info.width;
    int bmp_h = info.height;
    int bmp_bpp = info.bit_count;

    printf("图片分辨率:%d×%d\n", info.width, info.height);

    // 计算一行中的无效字节数
    int pad = (4 - (bmp_w*bmp_bpp/8 % 4)) % 4;
    int bmp_line_size = bmp_w * bmp_bpp / 8 + pad;
    int bmp_size = bmp_line_size * bmp_h;

    char *rgb = malloc(bmp_size);
    if(rgb == NULL)
    {
        perror("malloc rgb failed");
        return;
    }
    bzero(rgb, bmp_size);

    // 读取bmp文件RGB数据
    while(bmp_size > 0)
    {
        int n = read(fd, rgb, bmp_size); // n <= bmp_size
        if(n == -1)
        {
            perror("read bmp failed");
            return;
        }
        bmp_size -= n;
    }

    // 将RGB数据写入LCD
    int pixel = bmp_bpp/8;

    int x = (lcd_w - bmp_w) / 2;
    x = x < 0 ? 0 : x;
    int y = (lcd_h - bmp_h) / 2;
    y = y < 0 ? 0 : y;

    // char *p1 = lcd->map+lcd_line_size*y + x*lcd_bpp/8;

    int w = bmp_w < lcd_w ? bmp_w : lcd_w;
    int h = bmp_h < lcd_h ? bmp_h : lcd_h;

    // 将整张BMP画上LCD
    // for(int j=0; j<bmp_h && j<lcd_h; j++)
    for(int j=0; j<bmp_h && j<lcd_h-y; j++)
    {
        int lcd_offset = lcd_line_size*j;
        int bmp_offset = bmp_line_size*(bmp_h-j-1);

        // 将图片的一行画上LCD
        // for(int i=0; i<bmp_w && i<lcd_w; i++)
        for(int i=0; i<bmp_w && i<lcd_w-x; i++)
        {
            memcpy(lcd->map+4*i + lcd_offset,
                   rgb+i*pixel + bmp_offset, pixel);
        }
    }

    // 释放资源
    close(fd);
    free(rgb);
    
}
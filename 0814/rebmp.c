#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

#include "bmp.h"


int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage : ./* <bmp>\n");
        exit(1);
    }

    int lcd = open("/dev/fb0", O_RDWR);
    if(lcd == -1)
    {
        perror("open lcd failed");
        exit(1);
    }
    struct fb_var_screeninfo vinfo;
    ioctl(lcd , FBIOGET_VSCREENINFO, &vinfo);

    int lcd_w = vinfo.xres;
    int lcd_h = vinfo.yres;
    int lcd_bpp = vinfo.bits_per_pixel;
    int lcd_size = lcd_h * lcd_w * lcd_bpp / 8;

    int bmp = open(argv[1], O_RDONLY);
    if(bmp == -1)
    {
        perror("open bmp failed");
        exit(1);
    }

    struct bitmap_header header;
    struct bitmap_info info;
    bzero(&header, sizeof(struct bitmap_header));
    bzero(&info, sizeof(struct bitmap_info));

    read(bmp, &header, sizeof(struct bitmap_header));
    read(bmp, &info, sizeof(struct bitmap_info));
    if(info.compression != 0)
    {
        struct rgb_quad quad;
        bzero(&quad, sizeof(quad));
        read(bmp, &quad, sizeof(quad));   
    }

    int bmp_width = info.width;
    int bmp_height = info.height;
    int bmp_bpp = info.bit_count;
    int pad = (4 - bmp_width * bmp_bpp / 8 % 4) % 4;
    int bmp_line_size = (bmp_width * bmp_bpp / 8) + pad;
    int bmp_size = bmp_line_size * bmp_height;

    char *rgb = malloc(bmp_size);
    // 纠错: 原来是 bzero(&rgb, ...), 把指针变量自身的地址当成了缓冲区, 从栈上连写 bmp_size 个字节直接写穿栈导致段错误; 应清空 rgb 指向的堆内存
    bzero(rgb, bmp_size);
    while(bmp_size > 0)
    {
        int n = read(bmp, rgb, bmp_size);
        // 纠错: 读到文件尾(返回0)或出错(返回-1)时若不退出会死循环, 且不能拿 n<=0 去减 bmp_size
        if(n == -1)
        {
            perror("read bmp failed");
            return -1;
        }
        // 纠错: 原来写成 bmp -= n, 减的是文件描述符, bmp_size 永远不变导致死循环, fd 变负数后 read 返回 -1 使 tmp 反向越界; 这里减的应是剩余字节数
        bmp_size -= n;
    }

    char *p = mmap(NULL, lcd_size, PROT_READ | PROT_WRITE
                        , MAP_SHARED, lcd , 0);
    // 纠错: 原来没检查返回值, mmap 失败返回 MAP_FAILED(-1), p 为 -1 时往里写就是段错误
    if(p == MAP_FAILED)
    {
        perror("mmap lcd failed");
        exit(1);
    }
    int pixel = bmp_bpp / 8;
    int lcd_wide_off = (lcd_w - bmp_width) / 2;
    int lcd_height_off = (lcd_h - bmp_height) / 2;
    if (lcd_wide_off < 0)
        lcd_wide_off = 0;
    if (lcd_height_off < 0)
        lcd_height_off = 0;

    char *p1 = p + lcd_bpp / 8 * lcd_w * lcd_height_off + lcd_bpp / 8 * lcd_wide_off;
    // 纠错: 居中 = 目标行列都加上偏移量(像素)再乘每像素字节数; 原来算好的偏移没用上, 且循环条件 j < lcd_h-bmp_height 在图片超过半屏时会截断或整图不显示
    for(int j = 0; j < bmp_height && j < lcd_h-lcd_height_off; j++)
    {
        
        int lcd_offset = j * lcd_w * lcd_bpp / 8;
        int bmp_offset = (bmp_height - 1 - j) * bmp_line_size;
        for(int i = 0; i < bmp_width && i < lcd_w-lcd_wide_off; i++)
        {
            memcpy(p1 + lcd_offset + i * lcd_bpp / 8,
                   rgb + bmp_offset + i * bmp_bpp / 8, pixel);
        }
    }

    munmap(p, lcd_size);
    free(rgb);
    close(lcd);
    close(bmp);

    return 0;

}

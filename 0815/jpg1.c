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
#include <errno.h>
#include <stdbool.h>

#include "jpeglib.h"
// 参数说明：
//   jpgdata: jpg图片数据
//   jpgsize: jpg图片大小
// 返回值说明：
//   成功：指向rgb数据的指针
//   失败：NULL
    int rgb_w ;
    int rgb_h ;
    int rgb_bpp ;//(比特)
char *jpg2rgb(const char *jpgdata, size_t jpgsize)
{
    // 1，声明解码结构体，以及错误管理结构体
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    // 2，使用缺省的出错处理来初始化解码结构体
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_decompress(&cinfo);

    // 3，配置该cinfo，使其从 jpgdata 中读取jpgsize个字节
    //    这些数据必须是完整的JPEG数据
    jpeg_mem_src(&cinfo, jpgdata, jpgsize);

    // 4，读取JPEG文件的头，并判断其格式是否合法
    if(!jpeg_read_header(&cinfo, true))
    {
        fprintf(stderr, "jpeg_read_header failed: "
            "%s\n", strerror(errno));
        return NULL;
    }

    // 5，开始解码
    jpeg_start_decompress(&cinfo);

    // 6，获取图片的尺寸信息
    printf("宽：  %d\n", rgb_w = cinfo.output_width);
    printf("高：  %d\n", rgb_h = cinfo.output_height);
    printf("色深：%d\n", rgb_bpp = cinfo.output_components * 8);
    // jpg_pitch = cinfo.output_width * cinfo.output_components / 8;

    // 7，根据图片的尺寸大小，分配一块相应的内存rgbdata
    //    用来存放从jpgdata解码出来的图像数据
    unsigned long linesize = cinfo.output_width * cinfo.output_components;
    unsigned long rgbsize  = linesize * cinfo.output_height;
    char *rgbdata = calloc(1, rgbsize);

    // 8，循环地将图片的每一行读出并解码到rgb_buffer中
    int line = 0;
    while(cinfo.output_scanline < cinfo.output_height)
    {
        unsigned char *buffer_array[1];
        buffer_array[0] = rgbdata + cinfo.output_scanline * linesize;
        jpeg_read_scanlines(&cinfo, buffer_array, 1);
    }

    // 9，解码完了，将jpeg相关的资源释放掉
    jpeg_finish_decompress(&cinfo);
    jpeg_destroy_decompress(&cinfo);

    return rgbdata;
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        fprintf(stderr, "Usage : ./a.out <jpg>");
        exit(1);
    }
    //准备lcd资源
    int lcd = open("/dev/fb0", O_RDWR);
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
    
    //解析jpg数据
    int jpg = open(argv[1], O_RDWR);
    if(jpg == -1)
    {
        perror("open jpg failed");
        exit(1);
    }
    long jpg_size = lseek(jpg, 0, SEEK_END);
    lseek(jpg, 0, SEEK_SET);
    char *jpg_data = calloc(1, jpg_size);
    char *pdata = jpg_data;
    int tmp_jpg_size = jpg_size;

    while(tmp_jpg_size > 0)
    {
        int n = read(jpg, pdata, tmp_jpg_size);
        if(n == -1)
        {
            perror("read jpg failed");
            exit(1);
        }
        if(n == 0) break;
        tmp_jpg_size -= n;
        pdata += n;
    }

    char *rgb = jpg2rgb(jpg_data, jpg_size);
    //图片信息

    char *p = mmap(NULL, lcd_size, PROT_READ | PROT_WRITE, MAP_SHARED, lcd, 0);
    // memset(p, 0x0, lcd_size);

    for(int j = 0; j < lcd_h && j < rgb_h; j++)
    {
        int lcd_off = j * lcd_bpp * lcd_w / 8;
        int rgb_off = j * rgb_w * rgb_bpp / 8;
        for(int i = 0; i < rgb_w && i < lcd_w; i++)
            memcpy(p + (i * lcd_bpp / 8) + lcd_off, 
                   rgb + (i * rgb_bpp / 8) + rgb_off, rgb_bpp / 8 );
    }    
    
    close(lcd);
    close(jpg);
    munmap(p, lcd_size);
    free(rgb);
    free(jpg_data);

    return 0;
}
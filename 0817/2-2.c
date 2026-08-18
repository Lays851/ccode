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

#include "bmp.h"

int bmp_w, bmp_h, lcd_w, lcd_h;

/* 全局缓存：预加载的 BMP 像素数据、framebuffer 映射 */
static char *pbmp_pressed  = NULL;
static char *pbmp_released = NULL;
static char *maplcd        = NULL;
static int   lcd_bpp       = 0;
static int   lcd_fd        = -1;
static int   lcd_size      = 0;

/* 加载 BMP 文件，返回像素数据缓冲区（调用者负责 free） */
static char *load_bmp(const char *bmp_path, int *out_w, int *out_h, int *out_bpp)
{
    int fd = open(bmp_path, O_RDONLY);
    if (fd == -1) {
        perror("open bmp failed");
        exit(1);
    }

    struct bitmap_header header;
    struct bitmap_info info;
    bzero(&header, sizeof(header));
    bzero(&info, sizeof(info));
    read(fd, &header, sizeof(header));
    read(fd, &info, sizeof(info));

    if (info.compression != 0) {
        struct rgb_quad quad;
        bzero(&quad, sizeof(quad));
        read(fd, &quad, sizeof(quad));
    }

    int w   = info.width;
    int h   = info.height;
    int bpp = info.bit_count;

    int pad       = (4 - ((w * bpp / 8) % 4)) % 4;
    int bmp_pitch = bpp * w / 8 + pad;
    int bmp_size  = bmp_pitch * h;

    char *pbmp = calloc(1, bmp_size);
    char *tmp_pb = pbmp;
    int remaining = bmp_size;
    while (remaining > 0) {
        int n = read(fd, tmp_pb, remaining);
        if (n < 0) {
            perror("read bmp failed");
            exit(1);
        }
        if (n == 0)
            break;
        remaining -= n;
        tmp_pb += n;
    }
    close(fd);

    if (out_w)   *out_w   = w;
    if (out_h)   *out_h   = h;
    if (out_bpp) *out_bpp = bpp;

    return pbmp;
}

/* 初始化 framebuffer，返回 mmap 地址 */
static void lcd_init(void)
{
    lcd_fd = open("/dev/fb0", O_RDWR);
    if (lcd_fd == -1) {
        perror("open lcd failed");
        exit(1);
    }

    struct fb_var_screeninfo vinfo;
    ioctl(lcd_fd, FBIOGET_VSCREENINFO, &vinfo);
    lcd_w   = vinfo.xres;
    lcd_h   = vinfo.yres;
    lcd_bpp = vinfo.bits_per_pixel;
    lcd_size = lcd_bpp * lcd_h * lcd_w / 8;

    maplcd = mmap(NULL, lcd_size, PROT_READ | PROT_WRITE,
                  MAP_SHARED, lcd_fd, 0);
    if (maplcd == MAP_FAILED) {
        perror("mmap failed");
        exit(1);
    }
}

/* 轻量级显示：仅将预加载的像素数据拷贝到 framebuffer */
static void lcd_show(char *pbmp, int bmp_bpp)
{
    int pad       = (4 - ((bmp_w * bmp_bpp / 8) % 4)) % 4;
    int bmp_pitch = bmp_bpp * bmp_w / 8 + pad;

    int mid_xoff = (lcd_w - bmp_w) / 2;
    int mid_yoff = (lcd_h - bmp_h) / 2;
    if (mid_xoff < 0) mid_xoff = 0;
    if (mid_yoff < 0) mid_yoff = 0;

    for (int j = 0; j < lcd_h && j < bmp_h; j++) {
        int lcd_off = lcd_w * lcd_bpp * j / 8;
        int bmp_off = (bmp_h - 1 - j) * bmp_pitch;
        for (int i = 0; i < lcd_w && i < bmp_w; i++) {
            memcpy(maplcd + (4 * i) + lcd_off + mid_xoff * lcd_bpp / 8 + mid_yoff * 1024 * 4,
                   pbmp + (bmp_bpp / 8 * i) + bmp_off, bmp_bpp / 8);
        }
    }
}

/* 清理资源 */
static void cleanup(void)
{
    if (maplcd != NULL && maplcd != MAP_FAILED)
        munmap(maplcd, lcd_size);
    if (lcd_fd != -1)
        close(lcd_fd);
    free(pbmp_pressed);
    free(pbmp_released);
}

int main(int argc, char *argv[])
{
    if (argc != 3) {
        printf("需要按钮按下与松开的图片\n");
        exit(1);
    }

    /* 预加载两张 BMP 图片 */
    int bmp_bpp;
    pbmp_pressed  = load_bmp(argv[1], &bmp_w, &bmp_h, &bmp_bpp);
    pbmp_released = load_bmp(argv[2], NULL, NULL, NULL);

    /* 初始化 framebuffer */
    lcd_init();

    /* 初始显示松开的按钮 */
    lcd_show(pbmp_released, bmp_bpp);

    int td = open("/dev/input/event6", O_RDONLY);
    if (td == -1) {
        perror("open touch_panel failed");
        exit(1);
    }

    struct input_event ev;
    int x = 0, y = 0;

    while (1) {
        bzero(&ev, sizeof(ev));
        read(td, &ev, sizeof(ev));

        if (ev.type == EV_ABS && ev.code == ABS_X) {
            x = ev.value;
        }
        if (ev.type == EV_ABS && ev.code == ABS_Y) {
            y = ev.value;
        }

        if (ev.type == EV_KEY && ev.code == BTN_TOUCH) {
            printf("(%d, %d)\n", x, y);
            if (x < (bmp_w + lcd_w) / 2 && x > (lcd_w - bmp_w) / 2 &&
                y < (bmp_h + lcd_h) / 2 && y > (lcd_h - bmp_h) / 2) {
                if (ev.value == 1)
                    lcd_show(pbmp_pressed, bmp_bpp);
                else
                    lcd_show(pbmp_released, bmp_bpp);
            } else {
                lcd_show(pbmp_released, bmp_bpp);
            }
        }
    }

    cleanup();
    close(td);
    return 0;
}
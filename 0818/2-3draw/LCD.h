#ifndef __LCD_H__
#define __LCD_H__

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <sys/types.h>

struct lcdinfo
{
    int fd;

    int w;
    int h;
    int bpp;
    int pitch;
    int size;

    char *map;
};

extern void lcd_release(struct lcdinfo *p);
extern bool lcd_init(struct lcdinfo *p);

#endif


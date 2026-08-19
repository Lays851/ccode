#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <strings.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <linux/input.h> 
#include <sys/mman.h>
#include <linux/fb.h>
#include <sys/ioctl.h>

#include "LCD.h"

void infection(struct lcdinfo lcd, int x, int y, int color)
{
    int xoff = lcd.bpp/8 * (x-1);
    int yoff = lcd.pitch * (y-1);
    for(int j = 0; j < 3; j++)
    {
        for(int i = 0; i < 3; i++)
        {
            memcpy(lcd.map + xoff + yoff + (4*i) + (j*1024*4), &color, 4);
        }
    }
}

int main(void)
{
    struct lcdinfo lcd;
    if(!lcd_init(&lcd))
        return 0;
    
    int fd = open ("/dev/input/event6", O_RDWR);
    if(fd == -1)
    {
        perror("open touch_panel failed\n");
        exit(1);
    }
    printf("<%s> (%d)\n", __FILE__, __LINE__);
    struct input_event ev;
    int x = -1, y = -1, cl = 0; 
    int color[] = {0x00FF0000, 0x0000FF00, 0x000000FF};
    while(1)
    {
        // printf("<%s> (%d)\n", __FILE__, __LINE__);
        bzero(&ev, sizeof(ev)); 
        read(fd, &ev, sizeof(ev));
        
        if(ev.type == EV_ABS && ev.code == ABS_X)
        {
            x = ev.value;
        }
        if(ev.type == EV_ABS && ev.code == ABS_Y)
        {
            y = ev.value;
        }
        if(ev.type == EV_KEY && ev.code == BTN_TOUCH && ev.value >= 1) 
        {   
            if(x > 0 && y > 0)
                infection(lcd, x, y, color[0]);
        }
    }

    lcd_release(&lcd);

    return 0;
}

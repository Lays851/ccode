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

int main(int argc, char *argv[])
{
    int td = open("/dev/input/event6", O_RDONLY);
    if(td == -1)
    {
        perror("open touch_panel failed ");
        exit(1);
    }
    int x, y;
    struct input_event ev;
    while(1)
    {
        bzero(&ev, sizeof(ev));
        read (td, &ev, sizeof(ev));

        if(ev.type == EV_ABS && ev.code == ABS_X)
        {
            x = ev.value;
        }
        if(ev.type == EV_ABS && ev.code == ABS_Y)
        {
            y = ev.value;
        }
        if(ev.type == EV_SYN)
        {
            printf("(%d, %d)\n" x, y);
        }
        if(ev.type == EV_KEY && ev.code == BTN_TOUCH)
        {
            if(ev.value == 1)
                printf("按下触摸屏");
            else
                printf("松开触摸屏");
        }
        
    }

    return 0;
}
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <unistd.h>


int color[] = {0x00FF3333, 0x00FFCC22, 0x0099FF33, 0x0033FFDD,
               0x005599FF, 0x009955FF, 0x00FF3EFF, 0x00880000};

void partshow(char *screen,int signal)
{
    for(int j = 0; j < 600 / 2; j++)
    {
        for(int i = 0; i < 1024 / 4; i++)
        {
            memcpy(screen + (i*4) + (j*1024*4), &color[signal], 4);
        }
    }
}

int main (void)
{
    int lcd = open("/dev/fb0", O_RDWR);
    if(lcd == -1)
    {
        perror("open lcd failed");
        exit(1);
    }

    char *p = mmap(NULL, 1024 * 600 * 4, PROT_WRITE | PROT_READ, MAP_SHARED, lcd ,0);
    if(p == MAP_FAILED)
    {
        fprintf(stderr, "failed:%s", strerror(errno));
        exit(1);
    }

    int signal = 0;
    int count = 0;
    while(1)
    {
        
        for(int i = 0; i < 4; i++)
        {
            partshow(p + (i*1024), (signal + i) % 8);
        }

        for(int i = 0; i < 4; i++)
        {
            partshow(p + (i*1024) + (1024 * 600/2) * 4, (signal + 7 - i) % 8);
        }
        signal++;
        sleep(1);
    }
}
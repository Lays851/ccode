#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdint.h>
// #define RED 0x00FF0000
// #define GREEN 0x0000FF00
// #define BLUE 0x000000FF

int main (void)
{
    int lcd = open ("dev/fb0", O_RDWR);
    if(lcd == -1)
    {
        perror("oepn failed");
    }

    char *p = mmap(NULL, 1024 * 600 * 4, PROT_READ|PROT_WRITE, MAP_SHARED, lcd, 0);

    uint32_t RED = 0x00FF0000;
    uint32_t GREEN = 0x0000FF00;
    uint32_t BLUE = 0x000000FF;
    for(int j=0; j < 600; j++)
    {
        for (int i=0; i < 1024; i++)
        {
            memcpy(p + i*4 + j*1024*4, &RED, 4);
        }
    }

    return 0;

}
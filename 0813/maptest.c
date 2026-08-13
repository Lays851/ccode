#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdint.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>


int main(void)
{
    int lcd = open("/dev/fb0", O_RDWR);
    if(lcd == -1)
    {
        perror("open lcd failed");
        exit(1);
    }

    printf("显示屏分辨率为%dx%d", 1024, 600);
    char *p = mmap(NULL, 1024 * 600 * 4, PROT_READ | PROT_WRITE, MAP_SHARED, lcd, 0);
    if(p == MAP_FAILED)
    {
        perror("false");
        exit(1);
    }

    uint32_t color[] = {0x00FF0000, 0x0000FF00, 0x000000FF, //红绿蓝
                        0x00FFFFFF, 0x00FFFF00, 0x00000000};//白  黑  

    for(int a = 0; ;a++)
    {
        int tmp = a % 3;
        //法国
        if(tmp == 0)
        {
            for(int i = 0; i < 200; i++)
            {
                for(int j = 0; j < 1024; j++)
                {
                    memcpy(p + (i * 1024 + j) * 4, &color[3], 4);
                }
            }
            for(int i = 200; i < 400; i++)
            {
                for(int j = 0; j < 1024; j++)
                {
                    memcpy(p + (i * 1024 + j) * 4, &color[2], 4);
                }

            }
            for(int i = 400; i < 600; i++)
            {
                for(int j = 0; j < 1024; j++)
                {
                    memcpy(p + (i * 1024 + j) * 4, &color[0], 4);
                }
            }
            }

            //2国
            else if(tmp == 1)
            {
                for(int i = 0; i < 600; i++)
                {
                    for(int j = 0; j < 341; j++)
                    {
                        memcpy(p + (i * 1024 + j) * 4, &color[2], 4);
                    }
                    for(int j = 341; j < 682; j++)
                    {
                        memcpy(p + (i * 1024 + j) * 4, &color[3], 4);
                    }
                    for(int j = 682; j < 1024; j++)
                    {
                        memcpy(p + (i * 1024 + j) * 4, &color[0], 4);
                    }
                }
            }

            //3国
            else
            {
                for(int i = 0; i < 200; i++)
                {
                    for(int j = 0; j < 1024; j++)
                    {
                        memcpy(p + (i * 1024 + j) * 4, &color[5], 4);
                    }
                }
                for(int i = 200; i < 400; i++)
                {
                    for(int j = 0; j < 1024; j++)
                    {
                        memcpy(p + (i * 1024 + j) * 4, &color[0], 4);
                    }

                }
                for(int i = 400; i < 600; i++)
                {
                    for(int j = 0; j < 1024; j++)
                    {
                        memcpy(p + (i * 1024 + j) * 4, &color[4], 4);
                    }
                }
            }
        sleep(1);
    }
    return 0;
}
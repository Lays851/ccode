#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <stdint.h>

int main(int argc , char *argv[])
{
    if(argc != 3)
    {
        printf("Usage : ./a.out <源文件> <目的文件>\n");
        return 1;
    }

    FILE *fp1 = fopen(argv[1], "r");
    if(fp1 == NULL)
    {
        printf("open<%s> failed:%s\n", argv[1], strerror(errno));
        return 1;
    }

    FILE *fp2 = fopen(argv[2], "w");
    if(fp2 == NULL)
    {
        perror("open failed");
        fclose(fp1);
        return 1;
    }

    while(1)
    {
        char buf[1024];
        // if(fgets(buf, sizeof(buf), fp1) == NULL)
        // {
        //     if(feof(fp1))
        //         break;
        //     else if(ferror(fp1))
        //     {
        //         perror("读取失败");
        //         break;
        //     }
        // }
        // fputs(buf, fp2);

        long a = ftell(fp1);
        int n = fread (buf , 20, 5, fp1);

        if(n == 5)
        {
            fwrite(buf,20 , 5, fp2);
        }
        else 
        {
            if(feof(fp1))
            {
                long b = ftell(fp1);
                fwrite (buf , b-a, 1, fp2);
                break;
            }
            else if(ferror(fp1))
            {
                perror("读取文件失败");
                break;
            }

        }

    }

    return 0;
}
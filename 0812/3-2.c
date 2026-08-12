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

#define OPEN_METH 0x1FF

char *get_file(int num)
{
    num &= OPEN_METH;
    char *res = malloc(sizeof(char) * 10);
    res[9] = '\0';
    int tmp;
    for (int j = 0; j < 3; j++)
    {
        tmp = num >> j;
        char c;
        if (j == 0)
            c = 'x';
        else if (j == 1)
            c = 'w';
        else
            c = 'r';

        for (int i = 0; i < 3; i++)
        {
            if (tmp & (0x1 << (i * 3)))
                res[(8 - j) - (i * 3)] = c;
            else
                res[(8 - j) - (i * 3)] = '-';
        }
    }

    return res;
}

int main (int argc, char *argv[])
{
    if (argc != 2)
    {
        printf ("Usage : ./a.out <dir>\n");
        exit(1);
    }

    DIR *dp = opendir(argv[1]);
    struct stat info;
    stat(argv[1], &info);
    if(!S_ISDIR(info.st_mode))
    {
        printf("打开的不是目录文件\n");
        exit(1);
    }

    chdir(argv[1]);
    while(1)
    {
        struct dirent *ep = readdir(dp);
        if(ep == NULL)
        {
            break;
        }
        if(ep->d_name[0] == '.')
            continue;
        bzero(&info, sizeof(struct stat));
        stat(ep->d_name, &info);
        
        short tmp = info.st_mode >> 12;
        // printf("%x\n", tmp);
        printf("%c", tmp == 0x8 ? '-' : 'd');
        printf("%s\t", get_file(info.st_mode));
        printf("%d\t", tmp == 0x8 ? 1 : 2);
        printf("%ld\t", info.st_size);

        time_t t = info.st_atim.tv_sec;
        char * str = ctime(&t);
        printf("%s\t", str);
        
        printf("%s\n", ep->d_name);

        bzero(&info, sizeof(struct stat));
    }

    return 0;
}
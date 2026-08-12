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
    // res[9] = '\0';
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
    struct stat info;
    stat(argv[1], &info);

    // printf ("%#x", info.st_mode); 
    printf("%s\n", get_file(info.st_mode)) ;
}
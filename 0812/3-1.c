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

int main(int argc ,char *argv[])
{
    if(argc != 2)
    {
        printf("Usage : ./a.out <file>\n");
        exit(1);
    }

    FILE *fp = fopen(argv[1], "r");
    if(fp == NULL)
    {
        perror("open failed");
        exit(1);
    }
    fseek(fp, 0, SEEK_END);
    int b = ftell(fp);
    printf("method one: %d\n", b);
    fseek(fp, 0, SEEK_END);
    
    struct stat info;
    stat(argv[1], &info);
    printf("method two: %ld\n", info.st_size);

    int fd = open(argv[1], O_RDONLY);
    int a = lseek (fd, 0 ,SEEK_END);
    printf ("method three : %d\n", a);

    return 0;
}
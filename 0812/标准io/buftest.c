#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    FILE *fp = fopen (argv[1], "w+");
    
    fputs("hello world !\n", fp);

    // int count = 0;
    // while(1)
    // {
    //     fputc('a', fp);
    //     struct stat st;
    //     stat("b.txt",&st);
    //     if(st.st_size > 0)
    //         break;
    //     count++;   
    // }
    // printf ("%d", count);

    // fread(NULL, 1, 1, fp);

    //设置无缓冲
    // setvbuf (fp, NULL, _IONBF, 0);

    //设置行缓冲
    char buf[1024];
    setvbuf (fp, buf, _IONBF, 1024);

    abort();
}
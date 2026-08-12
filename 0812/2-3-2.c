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

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        printf("Usage: ./a.out <file> <file>");
        exit(1);
    }

    int line = 0;;
    FILE *fp1 = fopen (argv[1], "r+");
    if(fp1 == NULL)
    {
        fp1 = fopen (argv[1], "w+");
        if(fp1 == NULL)
        {
            printf("open line file  failed");
            exit(1);
        }
    }
    else
        fread (&line, 4, 1, fp1);

    fseek(fp1, 0, SEEK_SET);

    FILE *fp2 = fopen (argv[2], "a+");
    while(1)
    {
        time_t t = time(NULL);
        char *str = ctime(&t);

        fprintf(fp2, "%d, %s", ++line, str);
        fflush(fp2);
        
        fseek(fp1, 0, SEEK_SET);
        fwrite(&line, 4, 1, fp1);
        fflush(fp1);
        
        printf("%d, %s", line, str);
        fflush(stdout);

        sleep(1);
    }

    return 0;
}
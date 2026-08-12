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
    if(argc != 2)
    {
        printf("Usage : ./a.out <file>\n");
        exit(1);
    }

    long line = 0;
    FILE *fp = fopen(argv[1], "a+");


    long a = ftell(fp);
    fseek(fp, 0, SEEK_END);

    long b = ftell(fp);
    fseek(fp, 0, SEEK_SET);
    
    time_t t = time(NULL);
    char *tmp = ctime(&t);
    line = (b - a) / (strlen(tmp) + 2);

    while(1)
    {
        t = time(NULL);
        char *str = ctime(&t);
        

        fprintf(fp, "%ld, %s", ++line, str);
        fflush(fp);
        sleep(1);
    }

    return 0;
}

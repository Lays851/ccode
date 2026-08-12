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


int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./a.out <dir>、\n");
        exit(1);
    }

    DIR *dp = opendir (argv[1]);
    if(dp == NULL)
    {
        perror("open failed");
        exit(1);
    }

    struct stat st;
    stat(argv[1], &st);
    if(!S_ISDIR(st.st_mode))
    {
        fprintf(stderr, "打开的不是目录文件\n");
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
        printf("%s ", ep->d_name);

        bzero(&st, sizeof(struct stat));
        stat(ep->d_name, &st);
        printf("%ld\n", st.st_size);
    }


    return 0;
}
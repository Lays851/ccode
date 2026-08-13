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

int main (int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("请输入正确的格式\n");
        exit(1);
    }

    printf("当前路径：%s\n", getcwd(NULL, 0));

    char str[100];
    DIR *dp = opendir(argv[1]);
    struct stat info;
    chdir(argv[1]);

    stat(argv[1], &info);
    if(S_ISDIR(info.st_mode))
    {
        struct dirent *ep = readdir(dp);        
    }

    
    getcwd(str, sizeof(str));
    printf("执行后路径：%s\n", str);

    return 0;
}
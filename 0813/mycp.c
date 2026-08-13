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

void copy_file(FILE *fp1, FILE *fp2)
{
    if(fp1 == NULL)
    {
        perror("open <src> failed");
        return;
    }

    char buf[1024];
    while(1)
    {
        int n = fread(buf, 1, 1024, fp1);
        if(n == 0)
        {
            if(feof(fp1))
                break;
            else if(ferror(fp1))
            {
                perror("读取失败");
                exit(1);
            }
        }

        fwrite(buf, 1, n, fp2);
    }
    // printf("复制成功\n");
}

void copy_dir(const char *str1, const char *str2)
{
    char ori_path[1024] = {0}; 
    char src_path[1024] = {0}; 
    char dst_path[1024] = {0}; 
    
    getcwd(ori_path, 1024);

    if(chdir(str1) == -1)
    {
        perror("error");
        exit(1);
    }
    getcwd(src_path, 1024);

    chdir(ori_path);
    // 先创建目标目录（如果不存在），再 chdir 进去
    DIR *dp2 = opendir(str2);
    if(dp2 == NULL)
    {
        mkdir(str2, 0777);
    }

    chdir(str2);
    getcwd(dst_path, 1024);
    chdir(src_path);
    DIR *dp1 = opendir(src_path);
    if(dp1 == NULL)
    {
        fprintf(stderr, "错误\n");
        exit(1);
    }
    printf("%d\n", __LINE__);
    
    while(1)
    {
        chdir(src_path);
        struct dirent *ep = readdir(dp1);
        if(ep == NULL)
            break;

        if(strcmp(ep->d_name, ".") == 0 || strcmp(ep->d_name, "..") == 0)
            continue;

        struct stat info;
        stat(ep->d_name, &info);
        if(S_ISREG(info.st_mode))
        {
            FILE *fp1 = fopen(ep->d_name, "r");
            chdir(dst_path);
            FILE *fp2 = fopen(ep->d_name, "w");
            copy_file(fp1, fp2);
            fclose(fp1); 
            fclose(fp2); 
        }

        else if(S_ISDIR(info.st_mode))
        {
            chdir(dst_path);
            mkdir(ep->d_name, 0777);
            chdir(ep->d_name);
            char path[1024] = {0};
            getcwd(path, 1024);

            chdir(src_path);
            copy_dir(ep->d_name, path);
        }
    }

}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        fprintf(stderr, "Usage: ./a.out <src> <dst>.\n");
        exit(1);
    }

    struct stat info;
    stat(argv[1], &info);
    if(S_ISREG(info.st_mode))
    {
        FILE *fp1 = fopen(argv[1], "r");
        FILE *fp2 = fopen(argv[2], "w");
        copy_file(fp1, fp2);
    
        fclose(fp1);
        fclose(fp2);
    }

    else if(S_ISDIR(info.st_mode))
    {
        copy_dir(argv[1], argv[2]);
    }

    else
        fprintf(stderr , "该文件不支持复制。\n");


    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int main(void)
{
    int fd = open("b.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    dup2(fd, 1);  // 将 stdout 重定向到 copy.c
    close(fd);                 // 关闭原始 fd，不再需要

    system("ls -l");           // 输出会写入 copy.c
    return 0;
}
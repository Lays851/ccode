#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc , char *argv[])
{
    // if(argc == 3)
    // {
    //     printf("正确用法：%s <源文件> <目标文件>", argv[0]);
    // }

    int fd1 = open (argv[1], O_RDONLY);
    if (fd1 == -1)
    {
        perror("Open failed");
        return -1;
    }

    // int fd2 = open (argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    // if (fd2 == -1 )  
    // {
    //     perror("Open failed");
    //     return -1;
    // }

    // char buf[1024];
    // while (1)
    // {
    //     int n1 = read (fd1, buf, sizeof(buf));
    //     if(n1 == -1)
    //     {
    //         perror("读取文件失败");
    //     }
    //     if(n1 == 0)
    //         break;

    //     int n2 = 0;
    //     char *p = buf;
    //     while(1)
    //     {
    //         n2 = write (fd2 , p, n1 );
    //         if(n1 == n2)
    //             break;
    //         n1 = n1 - n2;
    //         p = p + n1;
    //     }
    // }

    char b[5]; int n1 = 4;
    int fd = open (argv[1], O_RDWR);
    read (fd, b, 5);
    int num1 = lseek (fd, 0, SEEK_END);
    int num2 = lseek (fd, 5000, SEEK_END);
    printf("%s %d %d\n", b, num1, num2);
    int num3 = lseek (fd, 4999, SEEK_END);

    write (fd, b, sizeof(b));

    // close(fd1);
    // close(fd2);
    close(fd);

    return 0;
}
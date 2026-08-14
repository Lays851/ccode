#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        perror("Usage: <src> <dst>\n");
        exit(1);
    }

    int fd_src = open(argv[1], O_RDONLY);
    int fd_dst = open(argv[2], O_WRONLY | O_CREAT, 0644);
    char buf[100];

    
    int nread, nwrite;
    while(1)
    {   
        //持续读取文件
        bzero(buf, 100);
        nread = read(fd_src, buf, 100);
        while(nread == -1 && errno == EINTR);
        
        if(nread == -1)
        {
            perror("read() failed");
            exit(1);
        }
        //返回值为0，读完该文件
        if(nread == 0)
        {
            break;
        }

        //写入文件
        char *p = buf;
        while(1)
        {
            nwrite = write(fd_dst, p, nread);
            while(nwrite == -1 && errno == EINTR);
            
            if(nwrite == -1)
            {
                perror("nwrite() failed");
                exit(1);
            }
            if(nwrite == 0)
            {
                break;
            }

            nread -= nwrite;
            p += nwrite;
        }
       
    }

    return 0;
    
}

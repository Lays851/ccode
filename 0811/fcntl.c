#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int main(void)
{
    int fd[2];
    pipe(fd);

    int state = fcntl (fd[0], F_GETFL);
    state |= O_NONBLOCK;
    fcntl (fd[0], F_SETFL, state);
    
    char buf[20];
    if(read(fd[0], buf, 20) > 0)
        printf("读取成功\n");
    else
        printf("没有数据\n");
    return 0;

}
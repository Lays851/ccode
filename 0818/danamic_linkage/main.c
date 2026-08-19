#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
    int fd = open("config", O_RDONLY);
    if(fd == -1)
    {
        perror("open config failed\n");
        exit(1);
    }
    char lib[50] = {0};
    read(fd, lib, 50);
    close(fd);

    void *handle = dlopen(strtok(lib, "\n"), RTLD_NOW);
    if(handle == NULL)
    {
        printf("dlopen failed:%s\n", dlerror());
        exit(1);
    }

    void (*detect)(void);
	detect = dlsym(handle, "detection");
    if(detect == NULL)
    {
        printf("查找失败:%s\n", dlerror());
        exit(1);
    }

    detect();
}
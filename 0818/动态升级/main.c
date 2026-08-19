#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/types.h>

int main(void)
{
    FILE *fp = fopen("config", "r");
    if(fp == NULL)
    {
        perror("open config failed\n");
        exit(1);
    }
    char lib[50] = {0};
    fgets(lib, 50, fp);
    fclose(fp);

    void *handle = dlopen(lib , RTLD_NOW);
    if(handle == NULL)
    {
        printf("dlopen failed: %s\n", dlerror());
        exit(1);
    }

    void (*detect)(void);
    detect = dlsym(handle, "detection");
    if(detect == NULL)
    {
        printf("not found sym:%s\n", strerror(errno));
        exit(1);
    }

    detect();
}
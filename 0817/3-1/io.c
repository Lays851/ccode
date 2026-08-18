#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

void myopen (const char *path, int flags, int *fd)
{
    *fd = open(path, flags);
    if(*fd == -1){
        printf("open %s failed\n", path);
        return;
    }
}

void myread (int fd, void *buf, size_t count, int *out)
{
    *out = read(fd, buf, count);
    if(*out < 0){
        printf("read failed\n");
        return;
    }
}
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "myio.h"

int main(int argc, char *argv[])
{
    int fd;
    myopen(argv[1], O_RDONLY, &fd);

    return 0;
}
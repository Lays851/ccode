#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void)
{
    int a = -3;

    int fd = open("a.bin", O_RDWR | O_CREAT | O_TRUNC, 0644);
    write(fd, &a, 4);
    close(fd);
    printf("abcd\n");

    bool b[2][3];
    printf("%ld", sizeof(b));

    return 0;
}
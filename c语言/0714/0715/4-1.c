#include <stdio.h>

int main(void)
{
    short i = 1;
    char *p = (char *)&i;

    if(*p == 1)
        printf("当前平台字节序为小端");
    else
        printf("当前平台字节序为大端");

    return 0;


}












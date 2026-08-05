#include <stdio.h>

extern int a ;
extern int f();

int main(void)
{
    printf("%d\n",a);
    // printf("%d",b);

    f(100);

    return 0;
}
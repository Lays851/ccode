#include <stdio.h>
int main(void)
{
    int a[4] = {1, 2, 3, 4};
    int i, *p;
    for(i=0, p=a; i<4; i++, p++)
    {
        printf("%d %d\n", *a+i, *p);
    }
    return 0;
}
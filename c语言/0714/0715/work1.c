#include <stdio.h>

int main(void)
{ 
    int a[2][3] = {{1,2,3},{4,5,6}};
    int (*p1)[3] = a;
    printf("%d\n%d", a[0][0], **p1);



    return 0;
}
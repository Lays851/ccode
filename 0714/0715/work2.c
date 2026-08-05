#include <stdio.h>

int main(int argc,char **argv)
{
    // int i ;
    // int *p ;
    // int **k ;
    // int a[3];
    // int *b[3];
    // int (*q)[3];
    // int (*r)(int);

    // int *p;
    // int a[2][2] = {1, 2, 3, 0};
    // p = a[0];
    // printf("%d, %d", *p, *(p+1)); // 输出什么？

    // int *p;
    // int a[2][2] = {{1, 0}, {2, 3}};
    // p= a[0];
    // printf("%d, %d\n", *p, *(p+1)); // 输出什么？

    int *p;
    int a[2][2] = {1, 2, 3, 0};
    p = a[0];
    printf("%d, %d", *p, *(p+1)); // 输出什么？

    return 0;


}
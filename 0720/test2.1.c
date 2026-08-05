#include <stdio.h>
extern void method(int);

void homwork_help(int a,void (*p)(int))
{
    printf("已自动完成作业\n");
    p(a);
}
#include <stdio.h>
extern void homwork_help(int a, void (*p)(int));


void method(int a)
{
    if(a == 1)
        printf("通过飞秋提交作业");
    if(a == 2)
        printf("通过邮箱提交作业");
}

int main(void)
{
    int a = 1; 
    homwork_help(a,method);

    return 0;
}
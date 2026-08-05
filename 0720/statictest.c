#include "myhead.h"

int a = 2;
static int b = 3;

int f(int a)
{
    printf("%d\n",a);
    printf("%d\n",b);
    printf("[%s]\n",__FUNCTION__);
    f2();
}
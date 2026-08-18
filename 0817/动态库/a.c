#include <stdio.h>

void fa(void)
{
    printf("这是%s中的%s函数\n", __FILE__, __FUNCTION__);
}
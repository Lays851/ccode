#include <stdio.h>

int f(int a ,int b ,int c)
{
    int big , max;
    big = a  >b ? a   : b;
    max = big>c ? big : c;

    return max;
    
}

int main()
{
    int a = 1;
    int b = 2;
    int c = 3;

    int max = f(a,b,c);
    printf("最大值为%d",max);

    return 0;
    
}
#include <stdio.h>

int cont(int n)
{
    if(n == 1)
        return 1;
    return cont(n-1) + 1;
}

int main(void)
{
    int m = 3;
    int n;
    n = cont(m);
    printf("%d",n);

    return 0;
}
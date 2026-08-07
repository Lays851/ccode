#include <stdio.h>
#include <stdbool.h>


bool issushu(int n)
{
    if (n <= 1)
        return false;
    if (n == 2)
        return true;

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }

    return true;
}

void respri(bool isPrime)
{
    if (isPrime)
        printf("是素数");
    else
        printf("不是素数");
}
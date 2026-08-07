#include <stdio.h>

double mypow(int a, int n)
{   if(n==0)
        return 1;

    if(n<0)
    {
    n = -n;
    double result = 1/(mypow(a,n-1) * a);
    return result;
    }

    double result = mypow(a,n-1) * a;
    return result;
}

int main(void)
{
    printf("%f", mypow(3,9));

    return 0;
}
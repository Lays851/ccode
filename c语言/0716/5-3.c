#include <stdio.h>

float myPower(float x,int n)
{
    float res;
    for(int i=0 ; i<n-1 ; i++)
    {
        res = x * x;
    }

    return res;
}

float yourPower(float x , int n)
{
    if(n == 1)
        return x;
    else
        return yourPower(x  , n-1) * x ;
}

int main(void)
{
    float ans1 = myPower(3.14,2);
    float ans2 = yourPower(8,3);
    printf("%f\n",ans1);
    printf("%f\n",ans2);

    return 0;
}
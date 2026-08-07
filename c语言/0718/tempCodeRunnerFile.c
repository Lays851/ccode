#include <stdio.h>
#include <math.h>

double opreat(double n)
{
    return cos(n);
}

void transform(int num,double *source,double *target,double (*p)(double))
{
    for(int i=0 ; i<num ; i++)
    {
        target[i] = (*p)(source[i]);
    }
}

int main(void)
{
    int num  = 3;
    double source[3] = {1,2,3};
    double target[3];
    double (*p)(double);

    p = opreat;
    transform(num, source, target, p);

    for(int i=0 ; i<num ;i++)
    {
        printf("%d\n",target[i]);
    }

    return 0;
}
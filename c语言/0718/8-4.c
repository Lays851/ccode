#include <stdio.h>
#include <math.h>


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
    double source[3] = {1.5,2,3};
    double target[3];
    double (*p)(double);
    p = sin;
    transform(num, source, target, p);
    printf("sin result:\n");
    for(int i=0 ; i<num ;i++)
        printf("%.6f\n",target[i]);

    p = cos;
    transform(num, source, target, p);
    printf("cos result:\n");
    for(int i=0 ; i<num ;i++)
        printf("%.6f\n",target[i]);
    return 0;
}
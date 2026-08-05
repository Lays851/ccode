#include <stdio.h>

int pfib(int n)
{

    if(n == 1 || n == 2)
    {    
        return 1;
    }
    else if(n <= 0)
    {
        return 0;
    }
    else
    {
        return (pfib(n-2) + pfib(n-1));
    }

}

int main(void)
{
    int n = 4;
    int num;
    num = pfib(n);

    printf("%d\n",num);

    return 0; 

}
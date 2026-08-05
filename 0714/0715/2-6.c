#include <stdio.h>

int main(void)
{
    char zimu[] = {"0123456789ABCDEF"};
    char num[20];
    int i = 0;
    char rsl[20];

    int n = -100;

    if(n < 0)
    {
        printf("-");
        n = -n;
    }
    if(n == 0)
        printf("%d",n);

    while(n > 0)
    {
        
        int yu = n % 16;
        n = n / 16;
        num[i] = zimu[yu];
        i++;
    }

    for(int j=0 ; i>=0 ; i-- , j++)
    {
        rsl[j] = num[i-1];
        printf("%c",rsl[j]);
    }

    return 0;


}
    
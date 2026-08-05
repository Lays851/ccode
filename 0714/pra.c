#include <stdio.h>
#include <unistd.h>

int main(void)
{
    for(int i = 1;;i++)
    {
        int t = i%11;
        if(t != 0)
            printf("%d",t);
        if(t == 10)
            printf("\n");
        else
            printf(" ");

    }

    return 0;
}


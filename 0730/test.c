#include <stdio.h>

int main(void)
{
    int num1 ,num2;

    while(1)
    {
        int n = scanf("%d %d", &num1, &num2);
        if(n == 2)
            break;

        //清空缓冲区
        else
        {
            printf("输入错误\n");
            while(getchar() != '\n');
        }
        
    }

    printf("%d\n", num1+num2);
    return 0;
}
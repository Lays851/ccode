#include <stdio.h>

int main(void)
{
    int num;
    printf("请输入一个整数");
    scanf("%d", &num);

    if (num < 2)
    {
        printf("没有小于或等于 %d 的素数\n", num);
        return 0;
    }

    printf("小于或等于 %d 的素数有：\n", num);

    for (int i = 2; i <= num; i++)
    {
        int a = 1;  

        for (int j = 2; j <= i / 2; j++)
        {
            if (i % j == 0)
            {
                a = 0;
                break;
            }
        }
        if (a)
        {
            printf("%d ", i);
        }
    }
    printf("\n");

    return 0;
}

#include <stdio.h>

int main(void)
{
    int a;
    float b;
    int c;

    printf("请输入一个整数和一个浮点数\n");
    while (1)
    {
        int n = scanf("%d %f", &a, &b);
        if (n == 2)
        {
            break;
        }
        else if (n == EOF)
        {
            printf("输入结束或发生错误\n");
            return 1;
        }
        else
        {
            while ((c = getchar()) != '\n' && c != EOF)
            {
            }
            printf("数据不合理请重新输入\n");
        }
    }

    printf("a:%d,b:%f\n", a, b);
    return 0;

}
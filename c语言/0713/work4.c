#include <stdio.h>

int main(void)
{
    double N, total;
    printf("请输入水的升数：");
    scanf("%le", &N);

    total = N * 3.34e25;
    printf("%.3e升水一共有%.3e个水分子\n", N, total);
    return 0;
}

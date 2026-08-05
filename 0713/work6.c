#include <stdio.h>

int main(void)
{
    int day0,week,day1;
    printf("请输入天数：");
    scanf("%d",&day0);

    week = day0/7;
    day1 = day0%7;

    printf("%d星期零%d天",week,day1);
    return 0 ;

}
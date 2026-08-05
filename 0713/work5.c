int main(void)
{
    int n ,num;
    num = 0;
    printf("请输入n的值：");
    scanf("%d",&n);

    for(;n > 0;n--)
    {
        num = num + n;
    }
    printf("和为：%d",num);

    return 0;
}
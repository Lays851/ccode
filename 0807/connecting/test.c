#include <stdio.h>
#include <string.h>
void f1(char a[],char b[])
{
    int count = 0;
    for(int i = 0;a[i]!='\n';i++)
    {
        if(a[i]!=' ')
        {
            b[count++]=a[i];
        }
    }
    b[count]='\n';
    printf("%s去掉空格后的字符串为：%s\n",a,b);
}
int main(void)
{
    char a[100]={0};
    char b[100]={0};
    printf("输入字符串按回车结束\n");
    fgets(a,100,stdin);
    f1(a,b);
    return 0;
}

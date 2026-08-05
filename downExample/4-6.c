#include <stdio.h>
#include <string.h>
#include <strings.h>

// 将a去重之后放入b
void strip(char a[], char b[])
{
    // 遍历a中d的每个字符
    for(int i=0, k=0; a[i]!='\0'; i++)
    {
        // 判定该字符是否存在于字符数组b中
        if(strchr(b, a[i]) == NULL)
        {
            b[k] = a[i];
            k++;
        }
    }
}

int main(int argc, char const *argv[])
{
    char a[100];
    char b[100]; // 随机值

    printf("请输入一个字符串:\n");
    fgets(a, 100, stdin);

    // 去除重复字符
    // 对数组b清零
    bzero(b, 100);
    // memset(b, 0, 100);
    strip(a, b);

    printf("去除重复字符之后：%s", b);

    return 0;
}

#include <stdio.h>
#include <limits.h>
#include <ctype.h>

void upper_case(char str[])
{
    int step = 'a' - 'A';
    for (int i = 0; str[i] != '\0'; i++)
    {
        if(islower(str[i]))
            str[i] -= step;
    }
}
int main(void)
{
    char str[] = "abcdefghijklnmopqrstuvwxyz";
    printf("原数组：%s\n", str);
    upper_case(str);
    printf("转换后：%s\n", str);

    return 0;
}
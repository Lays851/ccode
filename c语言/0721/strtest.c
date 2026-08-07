#include <stdio.h>
#include <stdbool.h>

bool strtest(const char *arr)
{
    const char *p;
    int num = 0;
    for (p = arr ; *p != '\0' ; p++)
        if(*p == '(')
            num++;
        else if(*p == ')')
            num--;
    return num;
}

int main(void)
{
    char *p1 = "(11)2(33)(4)";
    char *p2 = "(111)3()(((((()))))))";

    bool a = strtest(p2);
    if(a == 0)
        printf("匹配");
    else
        printf("不匹配");

        return 0;

}
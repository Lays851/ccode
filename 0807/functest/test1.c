#include <stdio.h>
#include <math.h>

int func(char *intstr, int intcount)
{
    int res = 0;
    if(intcount == 0)
        return 1;

    res = intstr[0] - '0';
    return (res * func(intstr + 1, intcount - 1));

}

int main(void)
{
    char *s = "1234";
    int res = 0;
    res = func(s, 4);
    // res = '1' - 48;

    printf("%d", res);
    return 0;
}
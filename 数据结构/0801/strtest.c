#include <stdio.h>
#include <string.h>

int main(void)
{


    char str[30] ;
    char str1[] = {'a', 'v', 'd','g'};

    strcpy(str, str1);

    printf("%d\n", sizeof(str));
    printf("%d\n", strlen(str));

    return 0;
}
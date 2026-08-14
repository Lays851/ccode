#include <stdio.h>

#define RATE 115200
#define STR(x) (char *)x 
int main(void)
{
    printf("%s\n",STR(RATE));

    return 0;
}
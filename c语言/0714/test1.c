#include <stdio.h>

int main(void)
{
    unsigned int data = 0x12ff0045;
    // 00010010 11111111 00000000 01000101
    // 00000000 00000000 11000000 00000000
    // 00000000 11000000 00000000 00000000
    #define FUN  0x0000c000
    #define FUN1 0x00c00000

    data = data | FUN;
    data = data & (~FUN1);

    printf("%#x",data);
    return 0 ;

}
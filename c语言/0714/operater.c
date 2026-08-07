#include <stdio.h>
#include <stdint.h>

int main(void)
{
    int a = 4,b = 3;
    printf("%d\n",!a);
    printf("%d\n",~b);



    #define FEN 0x0000FF00
    uint32_t mode = 0x30660006;//  00110000 01100110 00000000 00000110

    mode |=   FEN;  //00110000 01100110 11111111 00000110
    printf("%#x\n",mode);
    mode &=  (~FEN);//00110000 01100110 00000000 00000110
    printf("%#x\n",mode);

    int x = 0x12345;

    int y1 = x%32;
    printf("%#x",y1);



    return 0;


}
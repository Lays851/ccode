#include <stdio.h>
#define PI 3.14

struct node1
{
    int a;//4
    char n;//1
    long b __attribute__((aligned(32)));//4
};

struct smarthome
{
    unsigned int fan:2;
    unsigned char light:4;
    unsigned long temp:6;
};

int main(void)
{
    struct smarthome home = {0};
    home.fan = 1;
    home.light = 6;
    home.temp = 30;
    
    printf("%ld\n",*(long *)(&home));
    printf("%ld\n",sizeof(struct smarthome));
    printf("%d\n",sizeof(struct node1));
    printf("=================\n");
    printf("%f",3 * PI);

    


    return 0;
}
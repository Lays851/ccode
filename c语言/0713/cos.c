#include <stdio.h>

int main(int argc, char **argv){

    int a ;
    *(float*)&a = 3.14;
    printf("%f",*(float*)&a);
}
#include <stdio.h>

int main(void)
{
    char c ;
    printf("请输入大写字母");
    scanf("%c",&c);

    int hang = c - 'A' + 1;
    for(int i=0 ; i<hang ;i++)
    {
        printf("\n");
        for(int j=0 ; j<hang-i-1 ; j++){
            printf(" ");
        }
        for(int j=0 ; j<i ; j++){
            printf("%c",'A'+j);
        }
        for(int j=i ; j>=0 ; j--){
            printf("%c",'A'+j);
        }
    }

    return 0;
}

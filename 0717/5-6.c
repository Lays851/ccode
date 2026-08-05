#include <stdio.h>

void dlspa(char arr[])
{
    int i , j;
    for(i=0, j=0 ; arr[i]!='\0'  ; i++)
    {
        if(arr[i] != ' ')
            arr[j++] = arr[i];
    }
    arr[j] = '\0';
} 

int main(void)
{
    char s[] = "asdfg  asd";
    dlspa(s);
    printf("%s",s);

    return 0;
}
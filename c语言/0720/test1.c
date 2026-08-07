#include <stdio.h>

void recur(char arr[],int n)
{
    if(n<=1)
        return;

    recur(arr+1,n-2);
    char temp;
    temp = arr[0];
    arr[0] = arr[n-1];
    arr[n-1] = temp;

}

int main(void)
{
    char pp[] = "asdfghjkl";
    recur(pp,sizeof(pp)-1);
    printf("%s",pp);

    return 0;
}
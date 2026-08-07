#include <stdio.h>

void recur(int a[], int k)
{
    if( k <= 1)
        return;

    recur( a+1, k-2 );
    int  tmp;
    tmp = a[0];
    a[0] = a[k-1];
    a[k-1] = tmp;
}

int main()
{
    int a[] = {1,2,3,4};
    recur(a,4);

    for(int i=0 ; i<4 ;i++)
    {
        printf("%d",a[i]);
    }



}
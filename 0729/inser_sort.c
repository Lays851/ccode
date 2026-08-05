#include <stdio.h>

int main(void)
{
    int arr[10] = {3,0,8,6,5,7,4,1,2,9};

    int tmp;
    for(int i = 1; i < 10;i++)
    {
        tmp = arr[i];
        int j = i-1;
        while(j >= 0 && arr[j] > tmp)
        {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = tmp;
    }

    for(int i=0; i<10; i++)
    {
        printf("%d ",arr[i]);
    }
    return 0;
}
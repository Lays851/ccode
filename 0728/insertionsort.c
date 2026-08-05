#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void insertsort(int data[], int len)
{
    int tem;
    int i, j;
    for( i=1; i<len; i++)
    {
        tem = data[i];
        for( j = i-1; j>=0; j--)
        {
            if(tem < data[j])
                data[j+1] = data[j];
            else
            { 
                break; 
            }            
        }
        data[j+1] = tem;
    }
}

void show(int data[], int num)
{
    for(int i=0; i<num; i++)
        printf("%d ", data[i]);
    printf("\n");
}

int main (void)
{
    srand(time(NULL));

    int i, data[10];
    for(i=0; i<10; i++)
    {
        data[i] = rand() % 1000;
    }

    printf("随机序列\n");
    show(data, 10);

    insertsort(data, 10);
    printf("从小到大排列\n");
    show(data, 10);

    return 0;
}

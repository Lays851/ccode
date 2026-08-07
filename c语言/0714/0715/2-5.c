#include <stdio.h>

void sum(int a[], int b[], int c[], int n)
{
    for (int i = 0; i < n; i++)
    {
        c[i] = a[i] + b[i];
        printf("%d ", c[i]);
    }
}

int main(void)
{
    int a[] = {1, 2, 3};
    int b[] = {4, 5, 6};
    int c[3];

    sum(a, b, c, 3);

    return 0;
}
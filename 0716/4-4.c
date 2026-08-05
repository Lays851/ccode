#include <stdio.h>

int sonArraymax(int a[], int n)
{
    int cur_sum = a[0];
    int max_sum = a[0];

    for (int i = 1; i < n; i++)
    {
        if ( cur_sum <= 0)
            cur_sum = a[i];
        else
            cur_sum += a[i];

        if (cur_sum > max_sum)
            max_sum = cur_sum;
    }

    return max_sum;
}

int main(void)
{
    int a[7] = {-2, -5, -1, -6, -4, -8, -6};
    int max_sum = sonArraymax(a, 7);
    printf("%d\n", max_sum);

    return 0;
}
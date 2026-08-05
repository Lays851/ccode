#include <stdio.h>
#include <string.h>

void copy(int m,int n,int arr1[m][n], int arr2[m][n])
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            arr2[i][j] = arr1[i][j];
        }
    }
}

int main(void)
{
    int a[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
    int b[3][3];
    // int c[2] = {1,2};

    copy(3,3,a,b);

    if (memcmp(a, b, sizeof a) == 0)
        printf("复制成功\n");

    return 0;
}
#include <stdio.h>#include <stdio.h>

int main(void)
{
    int a[2][3] = {{1, 2, 3}, {4, 5, 6}};
    int (*p[2])[3];
    int i, j;
    int num = 0, total = 0;

    for (i = 0; i < 2; i++)
    {
        p[num++] = &a[i];
    }

    for (i = 0; i < num; i++)
    {
        for (j = 0; j < 3; j++)
        {
            total += (*p[i])[j];
        }
    }

    printf("和为:%d\n", total);


    char aa[] = "adasd";
    printf("%d",sizeof(aa));

    return 0;
}
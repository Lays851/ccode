#include <stdio.h>

void arrange(int left[],  int stack[],
            int stack_top, int right[], int right_len,int n)
    {
        if(n == 0 && stack_top == 0)
        {
            for(int i=0; i<right_len; i++)
            {
                printf("%d ", right[i]);
            }
            printf("\n");
            return;
        }

        if(n > 0 )
        {
            stack[stack_top] = left[0];
            int new_left[n-1];
            for(int i = 1; i < n; i++)
                new_left[i-1] = left[i];
            arrange(new_left, stack, stack_top + 1, right, right_len, n-1);
        }

        if(stack_top > 0)
        {
            right[right_len] = stack[stack_top-1];
            arrange(left, stack, stack_top-1, right, right_len+1, n );
        }

    }

int main(void)
{
    int n;
    printf("请输入n的值\n");
    scanf("%d", &n);

    int left[n], stack[n], right[n];

    for(int i=0; i<n; i++)
    {
        left[i] = i + 1;
    }

    arrange(left, stack, 0, right, 0, n);

    return 0;
}
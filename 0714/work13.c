#include <stdio.h>

int main(void)
{
    
    int num,ori,total = 0;

    while(1)
    {
        printf("请输入非零自然数");
        scanf("%d",&num);
        ori = num;

        while(1)
        {ULLONG_MAX
            if(num == 1)
                break;
            else if((num%2) == 0)
            {
                num = num / 2;            
            }
            else if((num%2) != 0)
            {
                num = 3 * num + 1;
            }
            total++;
        }
        printf("自然数%d经过%d次变换到达谷底",ori,total);
        
    }
    
    
    return 0;

}
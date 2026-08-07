#include <stdio.h>

int main(void)
{
    unsigned int num[3] = {0x12344520,0xff004B1C, 0x00553C1E};
    unsigned int data;

    for(int i=0 ; i<3 ; i++)
    {
        data = num[i];
        printf("第%d个数据",i+1);
        int d1,d2,d3,d4;
        int l1,l2,l3,l4;

        #define FUN 0xFF
        int temp = data & FUN;
        printf("温度为:%d摄氏度\n",temp);

        int shui = data>>8 & FUN;
        printf("湿度为%d\n",shui);

        d1 = data>>16 & 0x1;
        printf("0门的状态为%d\n",d1);
        d2 = data>>17 & 0x1;
        printf("1门的状态为%d\n",d2);
        d3 = data>>18 & 0x1;
        printf("2门的状态为%d\n",d3);
        d4 = data>>19 & 0x1;
        printf("3门的状态为%d\n",d4);

        l1 = data>>20 & 0x1;
        printf("0灯的状态为%d\n",l1);
        l2 = data>>21 & 0x1;
        printf("1灯的状态为%d\n",l2);
        l3 = data>>22 & 0x1;
        printf("2灯的状态为%d\n",l3);
        l4 = data>>23 & 0x1;
        printf("3灯的状态为%d\n",l4);

        
    }

    return 0;
}
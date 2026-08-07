#include <stdio.h>

int main(void)
{
	float fah;
    float cel;

	printf("请输入华氏温度:\n");
    while(1)
    {
        // 输入数字
	    if(scanf("%f", &fah) == 1 && (getchar() == '\n'))
            break;

        // 输入非数字，清空缓冲区
        while(getchar()!='\n');
        printf("请输入数字\n");
    }

	cel = (5*(fah-32)) / 9;

	printf("华氏%.2f° = 摄氏%.2f°\n", fah, cel);
	return 0;
}
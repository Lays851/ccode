#include "sqlist.h"

int main(void)
{   
    int n;
    sqlist *sql = init_sqlist(10);
    printf("请输入放入的数据，输入非数字结束：");

    while(scanf("%d",&n) == 1)
    {
        add_data(sql,n);
    }
    output(sql);
    ppsort(sql);
    output(sql);

    return 0;
}
#include "kernel.h"

int main(void)
{
    //初始化，不放有效数据
    listnode *linklist = init_List();
    int num;

    //创建新节点，循环赋值（打印出来）
    // 1 2 3 4 5 6 7 8
    printf("请输入数据的个数：");
    scanf("%d",&num);
    for(int i = 1; i <= num; i++)
    {   
        listnode *new = newnode(i);
        list_add_tail(&linklist->list, &new->list);
    }
    show(linklist);

    //重新排序
    sort(linklist);
    show(linklist);

    return 0;

}
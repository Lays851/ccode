#include "list.h"

int main(void)
{
    //初始化空双循环链表
    node *list = init_list();
    if(list)
        printf("初始化成功。");
    else
        perror("初始化失败");


    //输入n个数据
    int n;
    scanf("%d",&n);
    for(int i = n; i > 0; i--)
    {
        node *new = newnode(i);
        add_node(list, new);
    }

    show_each(list);

    sort(list);
    show_each(list);

    return 0;
}
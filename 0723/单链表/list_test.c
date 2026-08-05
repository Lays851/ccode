#include <stdio.h>
#include "list.h"

int main(void)
{
    node *mylist = init_list();

    int n ;
    scanf("%d",&n);
    for(int i = 1; i <= n;i++)
    {
        node *new = newnode(i);
        addtail_node(mylist,new);
    }

    show_each(mylist);

    destroy_list(mylist);

    return 0;
}
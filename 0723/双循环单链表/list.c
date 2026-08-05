#include "list.h"

node *init_list(void)
{
    node *init = malloc(sizeof(node));
    if(init != NULL)
    {
        init->next = init;
        init->prev = init;
    }
    return init;
}

node *newnode(int data)
{
    node *new = malloc(sizeof(node));
    if(new != NULL)
    {
        new->data = data;
        new->next = new ;
        new->prev = new ;
    }
    return new; 
}

void add_node(node *list, node *new)
{   
    node *tem = list->next;
    new->next  = tem ;
    new->prev  = list;
    list->next = new ;
    tem->prev  = new ;
}

bool isEmpty(node *list)
{
    return list->next == list;
}

void show_each(node *list)
{
    if(isEmpty(list))
        return;

    node *tem = list->next;
    do{
        printf("%d ",tem->data);
        tem = tem->next;
    }while(tem != list);

    printf("\n");
}

void sort(node *list)
{
    if(isEmpty(list))
    {
        return;
    }

    node *first = list;
    node *tem   = list->next;
    node *front ;
    while(front != first)
    {
        front = tem->next;
        if(front == first)
            break;
        if(tem->data % 2 == 0)
        {   //断开原来的连接
            tem->prev->next = tem->next;
            tem->next->prev = tem->prev;
            //连接至first之前
            tem->next = first;
            tem->prev = first->prev;
            first->prev->next = tem;
            first->prev = tem;
            //重新校准指针的位置
            first = tem;
        }
        tem = front;
    }
}

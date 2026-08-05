#include "list.h"

node *init_list(void)
{
    node *head = malloc(sizeof(node));
    if(head != NULL)
    {
        head->next = NULL;
    }
    return head;
}

node *newnode(int data)
{
    node *new = malloc(sizeof(node));
    if(new != NULL)
    {
        new->data = data;
        new->next = NULL;
    }
    return new;
}

void add_node(node *list, node *new )
{
    if(list == NULL || list == NULL)
        return;
    new->next = list->next;
    list->next = new;
}

void addtail_node(node *list, node *new )
{   
    node *tem = list;
    while(tem->next != NULL)
    {
            tem = tem->next;
    }
    tem->next = new;
}


bool isEmpty(node *list)
{
    return list->next == NULL;
}

void show_each(node *list)
{
    if(isEmpty(list))
    {
        return;
    }
    while(list->next != NULL )
    {
        printf("%d ",list->next->data);
        list = list->next;
    }
}

void destroy_list(node *list)
{   
    node *tem = list->next;
    while(tem != NULL)
    {
        free(list);
        list = tem;
        tem = tem->next;
    }
}


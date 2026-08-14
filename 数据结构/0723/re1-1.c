#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>



typedef struct node
{
    int data;
    struct node *next;
}node;

node *init_list(void)
{
    node *init = malloc(sizeof(node));
    if(init != NULL)
    {
        init->next = NULL;
    }
    return init;
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

bool isEmpty(node *list)
{
    return list->next == NULL;
}

void addtail(node *list, node *new)
{
    node *tem = list ;
    while(tem->next != NULL)
    {
        tem = tem->next;
    }
    tem->next = new;
}

void reverse(node *list)
{
    node *tem = list->next;
    node *next;
    list->next = NULL;


    while(tem != NULL)
    {
        next = tem->next;
        tem->next = list->next;
        list->next = tem;
        tem = next;
        
        
    }
}

void show(node *list)
{
    if(isEmpty(list))
        return;

    node *tem = list->next;
    while(tem != NULL)
    {
        printf("%d ",tem->data);
        tem = tem->next;
    }
    printf("\n");
}

int main(void)
{
    //初始化空链表
    node *list = init_list();

    //存储10个数据
    for(int i = 1; i <= 10; i++)
        addtail(list,newnode(i));

    show(list);
    //逆转
    reverse(list);
    show(list);

    return 0;
}
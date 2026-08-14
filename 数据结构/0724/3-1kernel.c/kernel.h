#ifndef __KERNEL_H
#define __KERNEL_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
//小结构体
struct list_head{
    struct list_head *next, *prev;
};

//大结构体
typedef struct list
{
    int data;
    struct list_head list;
}listnode, *linklist;

static listnode *init_List()
{
    listnode *head = malloc(sizeof(listnode));
    if(head != NULL)
    {
        head->list.next = &head->list;
        head->list.prev = &head->list;
    } 
    return head;
}

static listnode *newnode(int data)
{
    listnode *new = malloc(sizeof(listnode));
    if(new != NULL)
    {
        new->data = data;
        new->list.next = &new->list;
        new->list.prev = &new->list;
    } 
    return new;
}

static void list_add_tail(struct list_head *head, struct list_head *new)
{
    new->next = head;
    new->prev = head->prev;

    head->prev->next = new;
    head->prev = new;
}

static bool isEmpty(listnode *linklist)
{
    return linklist->list.next == &linklist->list;
}

static void show(listnode *linklist)
{
    if(isEmpty(linklist))
        return;

    struct list_head *first = linklist->list.next;
    struct list_head *head = &linklist->list;
    listnode *pos;
    for(; first != head; first = first->next)
    {
        pos = (listnode *)((char *)(first) - (char *)(&((listnode *)0)->list));
        printf("%d ",pos->data);
    }
    printf("\n");
}

static void sort(listnode *linklist)
{
   struct list_head *tem   = linklist->list.next;
   struct list_head *first = &linklist->list;

    while(tem != first )
    {
        struct list_head *front = tem->next;
        if(front == first)
            break;
        listnode *pos = (listnode *)((char *)(tem) - (char *)(&((listnode *)0)->list));
        if(pos->data % 2 == 0)
        {
            tem->prev->next = tem->next;
            tem->next->prev = tem->prev;

            tem->next = first;
            tem->prev = first->prev;
            first->prev->next = tem;
            first->prev = tem;

            first = tem;
        }
        tem = front;
    }
}

#endif
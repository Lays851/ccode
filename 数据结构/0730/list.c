#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
    struct node *prev;
}node;

node *init_list()
{
    node *init = malloc(sizeof(node));
    if (init == NULL) 
    {
        printf("malloc error");
        return NULL;
    }
    init->next = init;
    init->prev = init;
    return init;
}

node *newnode(int data)
{
    node *new = malloc(sizeof(node));
    if (new == NULL) 
    {
        printf("malloc error");
        return NULL;
    }
    new->data = data;
    new->next = new;
    new->prev = new;
    return new;
}

void list_add_tail(node *head, node *new)
{
    new->next = head;
    new->prev = head->prev;

    head->prev->next = new;
    head->prev = new;
}

void show(node *list)
{
    node *p = list->next;
    while (p != list)
    {
        printf("%d ",p->data);
        p = p->next;
    }
    printf("\n");
}

void list_del(node *del)
{
    del->prev->next = del->next;
    del->next->prev = del->prev;
}

node *list_destroy(node *head)
{
    while (head->next != head)
    {
        node *del = head->next;
        list_del(del);
        free(del);
    }
    return head;
}

int main(void)
{
    node *head = init_list();
    for(int i=1; i<=10; i++)
    {
        node *new = newnode(i);
        list_add_tail(head, new);
    }
    show(head);
    head = list_destroy(head);
    free(head);

    return 0;
}
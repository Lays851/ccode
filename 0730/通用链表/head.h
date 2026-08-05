#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef DATATYPE
#define DATATYPE int
#endif

typedef DATATYPE datatype;

typedef struct node
{
    datatype data;
    struct node *next;
    struct node *prev;
}node;

static node *init_list(void)
{
    node *head = malloc(sizeof(node));
    if(head == NULL)
        return NULL;
    head->next = head;
    head->prev = head;
    return head;
}

static node *newnode(datatype data, void(*assign)(datatype *, datatype))
{
    node *new = malloc(sizeof(node));
    if(new == NULL)
        return NULL;

    if(assign != NULL)
        assign(&new->data, data);
    else
        new->data = data;

    new->next = new;
    new->prev = new;
    return new;
}

static void insert_list(node *new, node *prev, node *next)
{
    new->next = next;
    new->prev = prev;
    prev->next = new;
    next->prev = new;
}

static node *list_add(node *head, node *new)
{
    insert_list(new, head, head->next);
    return new;
}

static node *list_add_tail(node *head, node *new)
{
    insert_list(new, head->prev, head);
    return new;
}

static void list_for_each(node *head, void(*show)(datatype))
{
    node *tmp = head->next;
    while(tmp != head)
    {
        show(tmp->data);
        tmp = tmp->next;
    }
}

static void list_del(node *head)
{
    head->prev->next = head->next;
    head->next->prev = head->prev;
}

static node *list_destroy(node *head, void(* release)(datatype *))
{
    node *tmp = head->next;
    while(tmp != head)
    {
        node *next = tmp->next;
        list_del(tmp);
        if(release != NULL)
            release(&tmp->data);
        free(tmp);  
        tmp = next;
    }
    return head;
}


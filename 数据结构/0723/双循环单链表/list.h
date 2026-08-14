#ifndef __LIST_H
#define __LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>

typedef struct node
{
    int data;

    struct node *next;
    struct node *prev;
}node;

node *init_list(void);
node *newnode(int data);
void add_node(node *list, node *new);
void del_node(node *list, node *new);
void show_each(node *list);
void destroy_list(node *list);
bool isEmpty(node *list);
void sort(node *list);

#endif
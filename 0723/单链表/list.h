#ifndef __LIST_H
#define __LIST_H
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}node;

node * init_list();
node * newnode(int data);
bool isEmpty(node *list);
void add_node(node *list, node *new);
void show_each(node *list);
void destroy_list(node *list);
void addtail_node(node *list, node *new);




#endif
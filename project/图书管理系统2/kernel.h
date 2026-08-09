#ifndef KERNEL_H
#define KERNEL_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

/* 通用双向链表: 节点与数据解耦, datanode 包装任意类型数据 */
typedef struct node
{
    struct node *next;
    struct node *prev;
} node;

typedef struct datanode
{
    void *data;          /* 指向堆上数据的指针, 任意类型 */
    size_t data_size;    /* 数据大小, 用于 free */
    struct node node;
} datanode;

/* 链表操作接口(实现在 kernel.c)
 * 模块化: 各模块(book/user/borrow)通过 include kernel.h 共用这一套链表 */
datanode *init_datanode(void);
datanode *new_datanode(void *data, size_t data_size);
void add_datanode(node *head, node *new);
bool del_datanode(node *head, void *data,
                  bool (*equal)(const void *, const void *));
void destroy_datanode(node *head);
void for_each_node(node *head, void (*show)(void *));

#endif /* KERNEL_H */

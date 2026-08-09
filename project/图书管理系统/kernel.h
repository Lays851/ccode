#ifndef KERNEL_H
#define KERNEL_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>

typedef struct node
{
    struct node *next;
    struct node *prev;
} node;

typedef struct datanode
{
    void *data;          // 指向堆上数据的指针，任意类型
    size_t data_size;    // 数据大小，用于 free
    struct node node;
} datanode;

static datanode *init_datanode()
{
    datanode *init = malloc(sizeof(datanode));
    if (init == NULL)
        return NULL;
    init->data = NULL;
    init->data_size = 0;
    init->node.next = &init->node;
    init->node.prev = &init->node;

    return init;
}

static datanode *new_datanode(void *data, size_t data_size)
{
    datanode *new = malloc(sizeof(datanode));
    if (new == NULL)
        return NULL;

    new->data = calloc(1,data_size);
    if (new->data == NULL)
    {
        free(new);
        return NULL;
    }

    memcpy(new->data, data, data_size);
    new->data_size = data_size;
    new->node.next = &new->node;
    new->node.prev = &new->node;

    return new;
}

static void insert_datanode(node *new, node *prev, node *next)
{
    new->next = next;
    new->prev = prev;
    prev->next = new;
    next->prev = new;
}

static bool isEmpty(node *head)
{
    return head->next == head;
}

static void add_datanode(node *head, node *new)
/* 修改: 参数顺序由 (new, head) 改为 (head, new), 头结点在前、新节点在后。
 * 原因: 原定义是 (new, head), 但调用处按习惯写成 (头, 新节点),
 *       传参错位导致链表结构错乱(新节点自环、头结点被当成数据节点),
 *       遍历时会造成死循环并崩溃。 */
{
    insert_datanode(new, head, head->next);
}

static bool del_datanode(node *head, void *data,
                         bool (*equal)(const void *, const void *))
{
    if (isEmpty(head))
        return false;

    node *temp = head->next;
    while (temp != head)
    {
        datanode *p = (datanode *)((char *)temp - (char *)&(((datanode *)0)->node));
        if (equal(p->data, data))
        {
            temp->prev->next = temp->next;
            temp->next->prev = temp->prev;

            temp->next = temp;
            temp->prev = temp;

            free(p->data);   // 释放节点内数据
            free(p);         // 释放节点本身

            return true;
        }

        temp = temp->next;
    }
    return false;
}

static void destroy_datanode(node *head)
{
    if (isEmpty(head))
        return;

    node *temp = head->next;
    while (temp != head)
    {
        node *next = temp->next;
        datanode *p = (datanode *)((char *)temp - (char *)&(((datanode *)0)->node));
        free(p->data);
        free(p);
        temp = next;
    }

    head->next = head;
    head->prev = head;
}

static void for_each_node(node *head, void (*show)(void *))
{
    if (isEmpty(head))
        return;

    node *tmp = head->next;
    while (tmp != head)
    {
        datanode *p = (datanode *)((char *)tmp - (char *)&(((datanode *)0)->node));
        show(p->data);
        tmp = tmp->next;
    }
}

#endif /* KERNEL_H */
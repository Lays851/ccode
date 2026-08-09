/* kernel.c - 通用双向链表实现
 * 模块化改造: 原 kernel.h 中所有 static 函数移到本文件,
 * 头文件只保留声明, 避免每个 .c 文件各复制一份链表代码 */
#include "kernel.h"

datanode *init_datanode(void)
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

datanode *new_datanode(void *data, size_t data_size)
{
    datanode *new = malloc(sizeof(datanode));
    if (new == NULL)
        return NULL;

    new->data = calloc(1, data_size);
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

/* 内部辅助: 把 new 节点挂到 prev 与 next 之间 */
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

void add_datanode(node *head, node *new)
{
    insert_datanode(new, head, head->next);
}

bool del_datanode(node *head, void *data,
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

            free(p->data);   /* 释放节点内数据 */
            free(p);         /* 释放节点本身 */

            return true;
        }

        temp = temp->next;
    }
    return false;
}

void destroy_datanode(node *head)
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

void for_each_node(node *head, void (*show)(void *))
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

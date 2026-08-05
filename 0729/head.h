#ifndef HEAD_H
#define HEAD_H

#ifndef DATATYPE
#define DATATYPE int
#endif

typedef DATATYPE datatype;

#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <time.h>
#include <unistd.h>

//哈希表元素的链式存储
typedef struct node
{
    datatype data;
    struct node *next;
}node;

//哈希表管理结构体
typedef struct hash_table
{
    node **table;
    int size;
}hash_table;

//初始化哈希表
hash_table *initHash(int size)
{
    hash_table *init = (hash_table *)calloc(1, sizeof(hash_table));
    if(init != NULL)
    {
        init->size = size;
        init->table = (node **)calloc(size, sizeof(node *));
        if(init->table == NULL)
        {
            free(init);
            return NULL;
        }
        // calloc 已经将指针数组初始化为 NULL
    }
    return init;
}

//新数据节点的建立
static node *newnode(datatype data)
{
    node *newnode = (node *)malloc(sizeof(node));
    if(newnode != NULL)
    {
        newnode->data = data;
        newnode->next = NULL;
    }
}

static void hash_add(hash_table *hash, datatype data, unsigned short(*p)(datatype data))
{
    if (hash == NULL || hash->size == 0)
        return;

    unsigned short pos = (*p)(data) % hash->size;
    node *mynode = newnode(data);

    if (mynode == NULL)
        return;

    node *tmp = hash->table[pos];
    if (tmp == NULL)
        hash->table[pos] = mynode;
    else
    {
        while(tmp->next != NULL)
            tmp = tmp->next;
        tmp->next = mynode;
    }
}

static int find(hash_table *hash_list, datatype data, unsigned short(*p)(datatype data))
{
    if (hash_list == NULL || hash_list->table == NULL || hash_list->size == 0)
        return -1;

    unsigned short pos = (*p)(data) % hash_list->size;
    node *tmp = hash_list->table[pos];
    if (tmp == NULL)
        return -1;

    while (tmp != NULL)
    {
        if (strcmp(tmp->data, data) == 0)
            return pos;
        tmp = tmp->next;
    }
    return -1;
}

#endif

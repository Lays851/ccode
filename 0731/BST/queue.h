#ifndef QUEUEDATA
#define QUEUEDATA int
#endif
#include <stdlib.h>



typedef QUEUEDATA datatype;

typedef struct datanode 
{
    datatype data;
    struct datanode *next;
} datanode;

typedef struct queue
{
    int size;
    struct datanode *front;
    struct datanode *rear;
} queue;

queue *init_queue(void)
{
    queue *q = malloc(sizeof(queue));
    if (q == NULL)
        return NULL;
    q->size = 0;
    q->front = NULL;
    q->rear = NULL;
    return q;
}

datanode *Queue_node(datatype data)
{
    datanode *n = malloc(sizeof(datanode));
    if (n == NULL)
        return NULL;
    n->data = data;
    n->next = NULL;
    return n;
}

void enQueue(queue *q, datanode *new)
{
    if (q->size == 0)
    {
        q->front = new;
        q->rear = new;
    }
    else
    {
        q->rear->next = new;
        q->rear = new;
    }
    q->size++;
}

datanode * outQueue(queue *q, datanode *out)
{
    if (q->size == 0)
        return NULL;

    out = q->front;
    q->front = q->front->next;
    q->size--;
    return out;
}

void for_each_Queue(queue *q, void (*visit)(datatype))
{
    datanode *n = q->front;
    while (n != NULL)
    {
        visit(n->data);
        n = n->next;
    }
}


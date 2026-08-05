#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#ifndef DATATYPE
#define DATATYPE int
#endif

typedef DATATYPE datatype;
struct queue_node
{
    datatype data;
    struct queue_node *next;
};

struct queue
{
    int size;
    struct queue_node *front;
    struct queue_node *rear;

};

static struct queue *init_queue(void)
{
    struct queue *init = calloc(1, sizeof(struct queue));
    init->size = 0;
    init->front = NULL;
    init->rear = NULL;
    return init;
}

static struct queue_node *newQnode(datatype data)
{
    struct queue_node *new = calloc(1, sizeof(struct queue_node));
    new->data = data;
    new->next = NULL;
    return new;
}

static void add_queue(struct queue *init, struct queue_node *new)
{
    if(init->size == 0)
    {
        init->front = new;
        init->rear = new;
    }
    else
    {
        init->rear->next = new;
        init->rear = new;
    }
    init->size++;
}

static struct queue_node* pop_queue(struct queue* init)
{
    struct queue_node *tmp = init->front;
    init->front = init->front->next;
    tmp->next = NULL;
    init->size--;
    return tmp;
}
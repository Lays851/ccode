#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

struct stacklist{
    int capacity;
    int top;
    int *data;
};

struct stacklist *initstack(int size)
{
    struct stacklist *stack = calloc(1, sizeof(struct stacklist));
    if(stack != NULL)
    {
        stack->data = calloc(size , sizeof(int));
        if(stack->data == NULL)
        {
            free(stack);
            return NULL;
        }
        stack->capacity = size;
        stack->top = -1;
    }
    return stack;
}

bool isFull(struct stacklist *stack)
{
    return stack->top + 1 == stack->capacity;
}
bool isEmpty(struct stacklist *stack)
{
    return stack->top == -1;
}

bool push(struct stacklist * stack, int data)
{
    if(isFull(stack))
        return false;
    
    stack->data[++stack->top] = data;
    return true;
}

bool pop(struct stacklist *stack, int *data)
{
    if(isEmpty(stack))
        return false;

    *data = stack->data[stack->top--];
    return true;
}

void show(struct stacklist *stack)
{
    if(isEmpty(stack))
        return;

    for(int i = 0; i <+ stack->top; i++)
    {
        printf("%d ",stack->data[i]);
    }
}

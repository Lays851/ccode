#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct node
{
    int *stack;
    int size;
    int top;
};

struct node *init_satck(int size)
{
    struct node *init = malloc(sizeof(struct node));
    if(init != NULL)
    {
        init->stack = calloc(size, sizeof(int));
        if(init->stack == NULL)
            return NULL;
    }
    init->size = size;
    init->top = -1;
    return init;
}

bool isFull(struct node *init)
{
    return init->top + 1 == init->size;
}

void push(struct node *init, int data)
{
    if(isFull(init))
        init  = realloc(init , init->size + 10*sizeof(int));

    init->stack[++init->top] = data;
}

bool isEmpty(struct node *init)
{
    return init->top == -1;
}

int pop(struct node *init)
{
    if(isEmpty(init))
        return -1;
    int num = init->stack[init->top--];
    return num;
}

int main(void)
{
    struct node *init = init_satck(100);
    int num, result = 0;
    printf("请输入一个十进制数：");
    scanf("%d",&num);

    while(num != 0)
    {
        int rem = num % 16;
        num = num / 16;

        push(init, rem);
    }

    while(!isEmpty(init))
    {
        int rem = pop(init);
        result += rem;
        result <<= 4;
    }
    result >>= 4;

    printf("%#x", result);   
    
}
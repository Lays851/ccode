#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct stacklist{
    int capacity;
    int top;
    int *data;
}setStack;

struct stacklist *initStack(int size)
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

bool top(struct stacklist *stack, int *data)
{
    if(isEmpty(stack))
        return false;

    *data = stack->data[stack->top];
    return true;
}

bool pop(struct stacklist *stack, int *data)
{
    if(top(stack, data))
    {
        stack->top--;
        return true;
    }
    return false;    
}

void show(struct stacklist *stack)
{
    if(isEmpty(stack))
        return;

    for(int i = 0; i <= stack->top; i++)
    {
        printf("%d ",stack->data[i]);
    }

    printf("\n");
}


int main(void)
{
    int num1, num2, num3;
    setStack *stack1 = initStack(3);     
    setStack *stack2 = initStack(3);     
    setStack *stack3 = initStack(3);
    
    for(int i = 3; i >= 1 ; i--)
    {
        push(stack1, i);
    }
    printf("一号栈的数据");
    show(stack1);

    printf("num1出栈进二号栈,num2出栈进三号栈\n");
    pop(stack1, &num1);
    printf("num1的值为%d\n",num1);
    push(stack2, num1);

    pop(stack1, &num2);
    printf("num2的值为%d\n",num2);
    push(stack3, num2);

    printf("num1出栈进三号栈,num3进二号栈\n");
    pop(stack2, &num1);
    push(stack3, num1);

    pop(stack1, &num3);
    push(stack2, num3);
    printf("二号栈");
    show(stack2);
    printf("三号栈");
    show(stack3);

    printf("num2,num1依次进二号栈\n");
    pop(stack3, &num1);
    pop(stack3, &num2);
    push(stack2, num2);
    push(stack2, num1);
    printf("二号栈");
    show(stack2);

    printf("所有数据还原最初状态\n");
    pop(stack2, &num1);
    pop(stack2, &num2);
    pop(stack2, &num3);

    push(stack1, num3);
    push(stack1, num2);
    push(stack1, num1);

    printf("一号栈");
    show(stack1);

    return 0;
}
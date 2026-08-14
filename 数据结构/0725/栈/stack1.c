#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

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

int main(void)
{
    //初始化空栈
    int size, data;
    printf("请输入需要转换的数据数量：");
    scanf("%d", &size);
    struct stacklist *stack = initstack(size);

    //入栈
    printf("请输入需要入栈的元素");
    for(int i = 0; i < size; i++)
    {
        scanf("%d", &data);   
        push(stack, data);
    }

    show(stack);

    printf("\n");
    //出栈并输出
    for(int i = 0; i < size; i++)
    {
        pop(stack, &data);
        printf("%#x ",data);
    }

    return 0;

}
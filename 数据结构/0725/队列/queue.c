#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct node
{
    int data;
    struct node *next;
}node;

typedef struct linkQueue
{
    node *front;
    node *rear ;
    int size; 
}linkQueue;

node *newnode(int data)
{
    node *new = malloc(sizeof(struct node));
    if(new != NULL)
    {
        new->data = data;
        new->next = NULL;
    }
    return new;
}

linkQueue *initQueue()
{
    linkQueue *Queue = malloc(sizeof(struct linkQueue));
    if(Queue != NULL)
    {
        Queue->front =NULL;
        Queue->rear =NULL;
        int size = 0;
    }
}

bool isEmpty(linkQueue *Queue)
{
    return Queue->size == 0;
}

bool find(linkQueue *Queue, int data)
{
    if(isEmpty(Queue))
        return false;

    node *tem = Queue->front;
    while(tem != NULL)
    {
        if(tem->data == data)
            return true;
        tem = tem->next;
    }  
    return false;  
}

bool pop(linkQueue *Queue)
{
    if(isEmpty(Queue))
        return false;

    node *node = Queue->front;
    Queue->front = Queue->front->next;
    node->next = NULL;
    Queue->size--;

    return true;
}

void push(linkQueue *Queue, int data)
{
    node *new = newnode(data);
    if(isEmpty(Queue))
    {
        Queue->front = new;
        Queue->rear = new;
        Queue->size++;
        return;
    }
    
    Queue->rear->next = new;
    Queue->rear = new;
    Queue->size++;

}

int main(void)
{
    //栈队列的初始化
    linkQueue *Queue = initQueue();
    int num;
    int cur = 0, max = 0;

    //用户输入数据入队
    printf("请输入景观标号(输入非数字结束)");
    while( scanf("%d",&num) == 1)
    {
    //查找队列中有无相同数据,没有就进栈，有就持续出栈直到丢掉该数据
        while(find(Queue, num))
        {
            pop(Queue);
            cur--;            
        }
        push(Queue, num);
        cur++;
        if(cur > max)
            max = cur;
    }

    printf("最多能选出%d个景点进行旅游。", max);

    return 0;
}
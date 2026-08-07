#include <stdio.h>
#include <stdlib.h>

//管理结构体
typedef struct node{
    int data;
    struct node *next;
}node;


//链表初始化
node *initList()
{
    node *head = malloc(sizeof(node));
    if (head != NULL)
    {
        head->next = NULL;
    }
    return head;
}

//建立新节点
node *newnode(int num)
{
    node *new = malloc(sizeof(node));
    if(new != NULL)
    {
        new->data = num;
        new->next = NULL;
    }
    return new;
}

//从头节点后插入新节点
void inserthead(node *head,node *new)
{
    new->next = head->next;
    head->next = new;
}

//各个节点逆转
void reverlist(node *list)
{
    if(list == NULL || list->next == NULL)
        return;
    node *prev = NULL;
    node *curr = list->next;
    node *next = NULL;

    while(curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    list->next = prev;
}

//输出链表数据
void show(node *list)
{
    while (list != NULL)
    {
        printf("%d ",list->data);
        list = list->next;
    }
    printf("\n");
}

int main(void)
{
    node *head = initList();
    int num;
    printf("请输入整数(输入0结束):");
    while(scanf("%d",&num) == 1)
    {   
        if(num == 0)
            break;
        node *new = newnode(num);
        if(new == NULL)
            break;
        inserthead(head,new);
    }

    reverlist(head);
    show(head->next);
    return 0;
}

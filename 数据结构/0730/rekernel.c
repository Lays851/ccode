#include <stdio.h>
#include <stdlib.h>

//小结构体
typedef struct loginode
{
    struct loginode *next;
    struct loginode *prev;
}loginode;

//大结构体
typedef struct datanode
{
    int data;
    struct loginode node;
}datanode;

datanode *init_data()
{
   datanode *init = calloc(1, sizeof(datanode));
   if(init == NULL)
    return NULL;

    loginode *node = &init->node;
    node->next = node;
    node->prev = node;
    return init;
}

//新建大节点
datanode *newnode(int data)
{
    datanode *new = calloc(1, sizeof(datanode));
    if(new == NULL)
     return NULL;
    new->data = data;
    new->node.next = new->node.prev = &new->node;
    return new;
}

void insert_node(loginode *new, loginode *prev, loginode *next)
{
    prev->next = new;
    new->prev = prev;
    next->prev = new;
    new->next = next;
}

void add_node(loginode *head, loginode *new)
{
    insert_node(new, head, head->next);
}

void add_node_tail(loginode *head, loginode *new)
{
    insert_node(new, head->prev, head);
}

void show(datanode *head)
{
    loginode *node = head->node.next;
    while(node != &head->node)
    {
        //根据loginode的地址，计算datanode的地址
        datanode *pos = (datanode *)((char *)(node) - (char *)(&((datanode *)0)->node));
        printf("%d ",pos->data);    
        node = node->next;
    }
    
    printf("\n");
}

loginode *del_node(loginode *node)
{
    node->prev->next = node->next;
    node->next->prev = node->prev;
    return node;
}

void sort(datanode *head)
{
    loginode *node = head->node.prev;
    while(node != &head->node)
    {
        loginode *prev = node->prev;
        datanode *pos = (datanode *)((char *)(node) - (char *)(&((datanode *)0)->node));
        if(pos->data % 2 == 0)
        {
            del_node(node);
            add_node_tail(&head->node, node);
        }
        node = prev;
    }
}

int main(void)
{
    int num;
    datanode *init = init_data();
    if(init)
        printf("初始化成功\n");
    else
        perror("初始化失败\n");

    printf("请输入一个整数：");
    scanf("%d",&num);

    for(int i=1; i<=num; i++)
    {
        datanode *new = newnode(i);
        add_node_tail(&init->node, &new->node);
    }
    show(init);

    sort(init);
    printf("排序后：\n");
    show(init);

    return 0;
}
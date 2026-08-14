#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}node;

node *initlist()
{
    node *head = malloc(sizeof(struct node));
    if(head == NULL)
        return NULL;
    head->next = NULL;
    return head;
}

node *newnode(int data)
{
    node *list = malloc(sizeof(struct node));
    if(list != NULL)
    {
        list->data = data;
        list->next = NULL;
    }
    return list;
}


void inserthead(node *head,node *new)
{
    new->next = head->next;
    head->next = new;
}

void show(node *list)
{   
    if(list == NULL){
        printf("\n");
        return;
    }
    node *p = list;
    do{
        printf("%d ",list->data);
        list = list->next;
    }while (list != NULL && list != p);
    
    printf("\n");
}

//单向循环链表每隔两个节点删除一个数据直到，只剩下2个数据
node *cutlist(node *list,int total,int n)
{
    if(list == NULL || total < n || n < 1)
        return NULL;

    node *prev = list;
    while(prev->next != list)
        prev = prev->next;
    node *curr = list;

    for(int i = 0; i < total - n; i++)
    {
        /* move prev and curr (n-1) steps to find the node to delete */
        for(int step = 1; step < 3; step++)
        {
            prev = prev->next;
            curr = curr->next;
        }

        prev->next = curr->next;
        curr->next = NULL;
        if(curr == list)
            list = curr->next;
        curr = curr->next;
    }

    return list;
}

int main(void)
{   
    int n,data;
    int cut_num = 2;
    int count = 0;
    node *list = initlist();
    node *first = NULL;

    printf("请输入节点的个数：\n");
    scanf("%d",&n);

    printf("请输入各个节点的数据：\n");
    while(scanf("%d",&data) == 1 && count < n)
    {
       
        node *new = newnode(data);
        if(new == NULL)
        {
            printf("分配新节点失败。\n");
            break;
        }
        if(count == n-1)
        {
            inserthead(list,new);
            /* 使列表循环：找到尾部并将其指向第一个元素 */
            first = list->next;
            if(first != NULL){
                node *tail = first;
                while(tail->next != NULL)
                    tail = tail->next;
                tail->next = first;
                /* detach dummy head */
                list->next = NULL;
                show(first);
            } else {
                printf("\n");
            }
            break;
        }
        inserthead(list,new);
        show(list->next);
        count++;
    }


    /* perform cutting on the circular list pointed by first */
    first = cutlist(first,n,cut_num);
    show(first);
    return 0;
}
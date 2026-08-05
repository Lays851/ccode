#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct node
{
    int data;
    struct node *next;
}node;


node *newnode(int num)
{
    node *new = malloc(sizeof(struct node));
    if(new != NULL)
    {
        new->data = num;
        new->next = new;
    }else{return NULL;};

    return new;
}

void insertList(node *first, node *new)
{
    node *tem = first;

    while (tem->next != first)
    {
        tem = tem->next;
    }

    new->next = first;
    tem->next = new;
}

void show(node *first)
{
    node *temp = first;
    do
    {
        printf("%d\t", temp->data);
        temp = temp->next;
    } while (temp != first);

    printf("\n");
}



int main(void)
{
    int n = 13;
    node *first = newnode(1);

    if (first == NULL)
    {
        return 1;
    }

    for (int i = 2; i <= n; i++)
    {
        node *new = newnode(i);
        if (new != NULL)
        {
            insertList(first, new);
        }
    }

    show(first);

    //从first开始每隔两个节点删除一个数据,直到最终只剩下两个节点
    node *start = first;

    for (int i = 0; i < n-2; i++)
    {
        node *prev = start->next;
        node *curr = prev->next;

        prev->next = curr->next;
        if (curr == first)
        {
            first = curr->next;
        }
        free(curr);
        start = prev->next;
    }

    show(first);

    return 0;
}
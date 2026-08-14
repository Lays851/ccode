struct node 
{
    int data;
    struct node *lchild;
    struct node *rchild;
};

#define DATATYPE struct node *
#include "queue.h"

#define TREENODE struct node 
#include "drawtree.h"

struct node *newnode(int data)
{
    struct node *new = calloc(1,sizeof(struct node));
    if(new != NULL)
    {
        new->data = data;
        new->lchild = NULL;
        new->rchild = NULL;
    }

    return new;
}

struct node *bst_add(struct node *root, struct node *new)
{
    if(root == NULL)
        return new;

    if(root->data > new->data)
        root->lchild = bst_add(root->lchild, new);
    if(root->data < new->data)
        root->rchild
     = bst_add(root->rchild , new);

    return root;
}

struct node *bst_delete(struct node *root, int data)
{
    if(root->data > data)
        bst_delete(root->lchild, data);
    if(root->data < data)
        bst_delete(root->rchild, data);

    if(root->data == data)
    {
        if(root->lchild != NULL)
        {
            struct node *tmp ;
            for(tmp = root->lchild; tmp->rchild != NULL; tmp = tmp->rchild);
            root->data = tmp->data;
            root->lchild = bst_delete(root->lchild, tmp->data);
        }
        else if(root->rchild != NULL)
        {
            struct node *tmp ;
            for(tmp = root->rchild; tmp->lchild != NULL; tmp = tmp->lchild);
            root->data = tmp->data;
            root->rchild = bst_delete(root->rchild, tmp->data);
        }
        else
        {
            free(root);
            return NULL;
        }
    }

    return root;
}

void prev_for_each(struct node *root)
{
    if(root == NULL)
        return;

    printf("%d ", root->data);
    prev_for_each(root->lchild);
    prev_for_each(root->rchild);
}

void mid_for_each(struct node *root)
{    
    if(root == NULL)
        return;

    mid_for_each(root->lchild);
    printf("%d ", root->data);
    mid_for_each(root->rchild);
}

void behide_for_each(struct node *root)
{
    if(root == NULL)
        return;

    behide_for_each(root->lchild);
    behide_for_each(root->rchild);
    printf("%d ", root->data);
}

void level_for_each(struct node *root)
{
    struct queue* init = init_queue();
    add_queue(init, newQnode(root));

    while(init->size != 0)
    {
        struct queue_node *tmp = pop_queue(init);
        printf("%d ",tmp->data->data);

        if(tmp->data->lchild != NULL)
            add_queue(init,newQnode(tmp->data->lchild));
        if(tmp->data->rchild
             != NULL)
            add_queue(init,newQnode(tmp->data->rchild));

    }

    printf("\n");
}

int main(void)
{
    struct node *root = NULL;
    int n;

    while(1)
    {
        scanf("%d", &n);

        if(n == 0)
            break;

        if(n > 0)
        {
            struct node *new = newnode(n);
            root = bst_add(root, new);
        }

        if(n < 0)
        {
            root = bst_delete(root, -n);
        }
    }

    draw(root);
    printf("前序: "); prev_for_each(root);   printf("\n");
    printf("中序: "); mid_for_each(root);    printf("\n");
    printf("后序: "); behide_for_each(root); printf("\n");
    printf("层序: "); level_for_each(root);


    return 0;
}
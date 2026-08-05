typedef struct node
{
    int data;
    struct node *lchild;
    struct node *rchild;
}node;

#define QUEUEDATA struct node *
#include "queue.h"

#define TREENODE node // 声明自定义的二叉树节点为TREENODE
#include "drawtree.h"

node *newNode(int data)
{
    node *new = malloc(sizeof(node));
    if (new != NULL)
    {
        new->data = data;
        new->lchild = NULL;
        new->rchild = NULL;
    }
    return new;
}

node *bstInsert(node *root, node *new)
{
    if(root == NULL)
        return new;

    if(root->data > new->data)
        root->lchild = bstInsert(root->lchild, new);

    else if (root->data < new->data)
        root->rchild = bstInsert(root->rchild, new);

    return root;
    
}

node *bstDelete(node *root, int data)
{
    if (root == NULL)
        return NULL;    

    if(root->data > data)
        root->lchild = bstDelete(root->lchild, data);

    else if(root->data < data)
        root->rchild = bstDelete(root->rchild, data);

    else 
    {
        //有左子树
        if (root->lchild != NULL)
        {
            node *p;
            for(p = root->lchild ; p->rchild != NULL; p = p->rchild);
            root->data = p->data;
            //删除左子树多余的节点
            root->lchild = bstDelete(root->lchild, p->data);

        }

        //没有左子树，有右子树
        else if (root->rchild != NULL)
        {
            node *p;
            for(p = root->rchild ; p->lchild != NULL; p = p->lchild);
            root->data = p->data;
            //删除左子树多余的节点
            root->rchild = bstDelete(root->rchild, p->data);

        }
        //没有子树，只有一个节点
        else
        {
            free(root);
            return NULL;
        }
    }

    return root;
}

void pre_order(struct node *root)
{
    if (root == NULL)
        return;
    printf("%d ", root->data);
    pre_order(root->lchild);
    pre_order(root->rchild);
}

void mid_order(struct node *root)
{
    if (root == NULL)
        return;
    mid_order(root->lchild);
    printf("%d ", root->data);
    mid_order(root->rchild);
}

void last_order(struct node *root)
{
    if (root == NULL)
        return;
    last_order(root->lchild);
    last_order(root->rchild);
    printf("%d ", root->data);
}

void level_order(struct node *root)
{
    if (root == NULL)
        return;

    queue *q = init_queue();
    //将根节点入队
    enQueue(q, Queue_node(root));

    //遍历队列
    while (q->size != 0)
    {
        //出队
        datanode *out ; 
        out = outQueue(q, out);
        printf("%d ", out->data->data);

        //依次加入左子树和右子树
        if (out->data->lchild != NULL)
            enQueue(q, Queue_node(out->data->lchild));
        if (out->data->rchild != NULL)
            enQueue(q, Queue_node(out->data->rchild));
    }
    printf("\n");
}


int main(void)
{
    node *root = NULL;
    int n;

    while(1)
    {
        scanf("%d", &n);
        if(n == 0)
            break;

        //插入与删除节点
        if (n > 0)
        {
            node *new = newNode(n);
            root = bstInsert(root, new);
        }

        if (n < 0)
        {
            root = bstDelete(root, -n);
        }
        
    }
    draw(root);   
    pre_order(root);printf("\n");
    mid_order(root);printf("\n");
    last_order(root);printf("\n");
    level_order(root);

 

    return 0;
}
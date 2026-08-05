#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

typedef struct tree
{
    int data;
    int height;
    struct tree *lchild;
    struct tree *rchild;
}linktree;

#define TREENODE linktree // 声明自定义的二叉树节点为TREENODE
#include "drawtree.h" // 包含画树代码


linktree *init_tree(int data)
{
    linktree *root = malloc(sizeof(linktree));
    if(root != NULL)
    {
        root->data = data;
        root->height = 1;
        root->rchild = NULL;
        root->lchild = NULL;
    }
    return root;
}

int height(linktree *root)
{
    if(root == NULL)
        return 0;
    return root->height;
}

linktree * avlRotateRight(linktree *root)
{
    linktree *tmp = root->lchild;
    root->lchild = tmp->rchild;
    tmp->rchild = root;

    //更新高度
    root->height = 1 + MAX(height(root->lchild), height(root->rchild));
    tmp->height = 1 + MAX(height(tmp->lchild), height(tmp->rchild));
    
    return  tmp;
}

linktree * avlRotateLeft(linktree *root)
{
    linktree *tmp = root->rchild;
    root->rchild = tmp->lchild;
    tmp->lchild = root;
    //更新高度
    root->height = 1 + MAX(height(root->lchild), height(root->rchild));
    tmp->height = 1 + MAX(height(tmp->lchild), height(tmp->rchild));

    return  tmp;
}

linktree * avlRotateLeftRight(linktree *root)
{
    root->lchild = avlRotateLeft(root->lchild);
    return avlRotateRight(root);
}

linktree * avlRotateRightLeft(linktree *root)
{
    root->rchild = avlRotateRight(root->rchild);
    return avlRotateLeft(root);
}

linktree *avl_insert(linktree *root, linktree *new)
{
    if(root == NULL)
        return new;

    if(new->data > root->data)
        root->rchild = avl_insert(root->rchild, new);
    else if(new->data < root->data)
        root->lchild = avl_insert(root->lchild, new);
    else
    {
        free(new);
        printf("该数据已经存在\n");
        return root; 
    }

    //判断平衡性
    if(height(root->lchild) - height(root->rchild) > 1)
    {
        if(new->data < root->lchild->data)
            root = avlRotateRight(root);
        else if(new->data > root->lchild->data)
            root = avlRotateLeftRight(root);
    }

    else if(height(root->rchild) - height(root->lchild) > 1)
    {
        if(new->data > root->rchild->data)
            root = avlRotateLeft(root);
        else if(new->data < root->rchild->data)
            root = avlRotateRightLeft(root);
    }
    root->height = 1 + MAX(height(root->lchild), height(root->rchild));
        
    return root;
}

linktree *avl_Remove(linktree *root, int data)
{
    if(root == NULL)
        return NULL;

    if(data > root->data)
        root->rchild = avl_Remove(root->rchild, data);
    else if(data < root->data)
        root->lchild = avl_Remove(root->lchild, data);

    else
    {
        linktree *temp ;
        if(root->lchild != NULL)
        {        
            for(temp = root->lchild; temp->rchild != NULL; temp = temp->rchild);
            root->data = temp->data;
            root->lchild = avl_Remove(root->lchild, temp->data);
        }
        else if(root->rchild != NULL)
        {
            for(temp = root->rchild; temp->lchild != NULL; temp = temp->lchild);   
            root->data = temp->data;
            root->rchild = avl_Remove(root->rchild, temp->data);
        }
        else
        {
            free(root);
            return NULL;
        }
    }

    //判断平衡性
    if(height(root->lchild) - height(root->rchild) > 1)
    {
        if(height(root->lchild->lchild) > height(root->lchild->rchild))
            root = avlRotateRight(root);

        else 
            root = avlRotateLeftRight(root);
    }

    if(height(root->rchild) - height(root->lchild) > 1)
    {
        if(height(root->rchild->lchild) > height(root->rchild->rchild))
            root = avlRotateLeft(root);
        
        else
            root = avlRotateRightLeft(root);
    }

    root->height = 1 + MAX(height(root->lchild), height(root->rchild));
    
    return root;
}


int main(void)
{
    linktree *root = NULL;
    int n;
    while(1)
    {
        scanf("%d", &n);
        if(n == 0)
            break;

        if(n > 0)
            root = avl_insert(root, init_tree(n));

        if(n < 0)
            root = avl_Remove(root, -n);
        draw(root);
    }

    

    return 0;
}

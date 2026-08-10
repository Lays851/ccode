/* borrow.c - 借阅模块: 借书/还书逻辑
 * 模块化改造: 从 main.c 中拆分出来
 * 依赖: book模块(查书/改库存) + user模块(user结构体与借阅链表)
 * 改造: kernel_list.h 下 find_book 直接返回 book*, 不再经过 datanode 包装 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "borrow.h"
#include "book.h"

/* 把 book 数据复制成借阅记录节点 */
static mapnode *mapping(book *ori)
{
    mapnode *map = calloc(1, sizeof(mapnode));
    if (map == NULL)
        return NULL;

    strcpy(map->bookname, ori->bookname);
    strcpy(map->author, ori->author);
    map->next = NULL;

    return map;
}

/* 借阅链表: 尾部挂接新节点 */
static mapnode *add_mapnode(mapnode *head, mapnode *new)
{
    if (new == NULL)
        return head;
    if (head == NULL)
        return new;

    mapnode *tmp = head;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return head;
}

/* 借阅链表: 按书名删除节点(并释放内存) */
static mapnode *del_mapnode(mapnode *head, char *name)
{
    if (head == NULL)
        return NULL;

    if (strcmp(head->bookname, name) == 0)   /* 删除头节点 */
    {
        mapnode *next = head->next;
        free(head);
        return next;
    }

    mapnode *tmp = head;
    mapnode *p = head->next;
    while (p != NULL)
    {
        if (strcmp(p->bookname, name) == 0)
        {
            tmp->next = p->next;
            free(p);
            return head;
        }
        tmp = p;
        p = p->next;
    }

    return head;
}

void borrow_book(user *cur_user, char *bookname)
{
    book *book_node = NULL;

    if (find_book(bookname, &book_node) && book_node->margin != 0)
    {
        cur_user->booksnum++;
        book_node->margin--;   /* 库存减一 */
        printf("借阅成功！\n");

        mapnode *record = mapping(book_node);
        cur_user->userborrow_list = add_mapnode(cur_user->userborrow_list, record);
    }
    else
    {
        printf("未找到该书或库存不足\n");
    }
}

void return_book(user *cur_user, char *bookname)
{
    book *book_node = NULL;

    if (find_book(bookname, &book_node))
    {
        cur_user->booksnum--;
        book_node->margin++;   /* 库存加一 */
        printf("归还成功！\n");
        cur_user->userborrow_list = del_mapnode(cur_user->userborrow_list, bookname);
    }
    else
    {
        printf("未找到该书\n");
    }
}

void brows_count(void)
{
    /* TODO: 遍历所有用户, 统计其 userborrow_list 的长度/书籍 */
    printf("功能开发中。。。\n");
}

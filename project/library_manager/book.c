/* book.c - 书籍模块: 管理书籍链表与书籍的增删改查
 * 改造: 从 kernel.h(datanode 包装式) 换用 kernel_list.h(Linux 内核链表, 节点内嵌式)
 * 优点: 不需要 kernel.c; 遍历/删除直接用 list_for_each_entry, 代码更简洁 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "book.h"

static LIST_HEAD(book_list);   /* 书籍链表头(模块私有) */

/* 打印一本书 */
static void bookshow(book *b)
{
    printf("书籍编号[%s], 书名《%s》, 作者：%s, 价格：%.1f, 库存：%d\n",
           b->bookid, b->bookname, b->author, b->price, b->margin);
}

void init_book_data(void)
{
    FILE *fp = fopen("book.txt", "r");
    if (fp == NULL)
    {
        printf("警告: book.txt 不存在, 书籍列表为空\n");
        return;
    }

    char id[20], name[40], author[20];
    double price;
    int margin;
    /* 修改: 原代码先 malloc 再 fscanf, EOF 时 tmp 泄漏且文件未关闭;
     * 改为先读入临时变量, 读取成功才分配节点 */
    while (fscanf(fp, "%19s %39s %19s %lf %d", id, name, author, &price, &margin) == 5)
    {
        book *b = malloc(sizeof(book));
        if (b == NULL)
            break;
        strcpy(b->bookid, id);
        strcpy(b->bookname, name);
        strcpy(b->author, author);
        b->price = price;
        b->margin = margin;
        list_add_tail(&b->node, &book_list);   /* 挂到链表尾部 */
    }
    fclose(fp);
}

void show_all_books(void)
{
    book *pos;
    list_for_each_entry(pos, &book_list, node)
        bookshow(pos);
}

bool find_book(char *name, book **out)
{
    book *pos;
    list_for_each_entry(pos, &book_list, node)
    {
        if (strcmp(pos->bookname, name) == 0)
        {
            *out = pos;
            return true;
        }
    }
    return false;
}

void add_book(char *id, char *name, char *author, double price, int margin)
{
    book *b = malloc(sizeof(book));
    if (b == NULL)
        return;
    strcpy(b->bookid, id);
    strcpy(b->bookname, name);
    strcpy(b->author, author);
    b->price = price;
    b->margin = margin;
    list_add_tail(&b->node, &book_list);
}

bool del_book(char *name)
{
    book *target = NULL;
    if (!find_book(name, &target))
        return false;
    list_del(&target->node);   /* 从链表摘下 */
    free(target);               /* 释放节点内存 */
    return true;
}

void update_book_author(char *name, char *author)
{
    book *target = NULL;
    if (find_book(name, &target))
        strcpy(target->author, author);
}

void update_book_price(char *name, double price)
{
    book *target = NULL;
    if (find_book(name, &target))
        target->price = price;
}

void search_book(char *name)
{
    book *target = NULL;
    if (find_book(name, &target))
        bookshow(target);
    else
        printf("未找到该书\n");
}

void destroy_book_data(void)
{
    /* list_for_each_entry_safe: 遍历时允许删除当前节点 */
    book *pos, *n;
    list_for_each_entry_safe(pos, n, &book_list, node)
    {
        list_del(&pos->node);
        free(pos);
    }
}

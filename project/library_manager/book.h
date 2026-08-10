#ifndef BOOK_H
#define BOOK_H

#include "kernel_list.h"
#include <stdbool.h>

/* 书籍数据: 结构体内嵌 struct list_head, 用 Linux 内核链表串联 */
typedef struct {
    char bookid[20];
    char bookname[40];
    char author[20];
    double price;
    int margin;   /* 库存 */
    struct list_head node;   /* 内嵌链表节点 */
} book;

/* 书籍模块接口(实现在 book.c)
 * 书籍链表是 book.c 的私有数据, 外部只能通过这些函数操作 */
void init_book_data(void);                                /* 初始化链表 + 从 book.txt 读取书籍 */
void show_all_books(void);                                /* 遍历打印所有书籍 */
bool find_book(char *name, book **out);                   /* 按书名查找, 找到返回 true 并输出 book* */
void add_book(char *id, char *name, char *author, double price, int margin);
bool del_book(char *name);                                /* 按书名删除, 返回是否成功 */
void update_book_author(char *name, char *author);        /* 修改作者 */
void update_book_price(char *name, double price);         /* 修改价格 */
void search_book(char *name);                             /* 查找并打印单本书 */
void destroy_book_data(void);                             /* 释放书籍链表内存 */

#endif /* BOOK_H */

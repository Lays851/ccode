#ifndef BOOK_H
#define BOOK_H

#include "kernel.h"

/* 书籍数据 */
typedef struct {
    char bookid[20];
    char bookname[40];
    char author[20];
    double price;
    int margin;   /* 库存 */
} book;

/* 书籍模块接口(实现在 book.c)
 * 书籍链表是 book.c 的私有数据, 外部只能通过这些函数操作 */
void init_book_data(void);                                /* 初始化链表 + 添加初始书籍 */
void show_all_books(void);                                /* 遍历打印所有书籍 */
bool find_book(char *name, datanode **out);               /* 按书名查找, 找到返回 true 并输出节点 */
void add_book(char *id, char *name, char *author, double price, int margin);
bool del_book(char *name);                                /* 按书名删除, 返回是否成功 */
void update_book_author(char *name, char *author);        /* 修改作者 */
void update_book_price(char *name, double price);         /* 修改价格 */
void search_book(char *name);                             /* 查找并打印单本书 */
void destroy_book_data(void);                             /* 释放书籍链表内存 */

#endif /* BOOK_H */

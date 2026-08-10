#ifndef USER_H
#define USER_H

#include "kernel_list.h"
#include <stdbool.h>

/* 用户借阅记录的链表节点(单向链表, 随 user 一起管理) */
typedef struct mapnode
{
    char bookname[40];
    char author[20];
    struct mapnode *next;
} mapnode;

/* 读者: 结构体内嵌 struct list_head, 用 Linux 内核链表串联 */
typedef struct {
    char userName[20];
    char password[20];
    int booksnum;
    mapnode *userborrow_list;   /* 该用户借阅的书籍链表 */
    struct list_head node;      /* 内嵌链表节点 */
} user;

/* 管理员 */
typedef struct {
    char admintId[20];
    char password[20];
    struct list_head node;      /* 内嵌链表节点 */
} admint;

/* 用户模块接口(实现在 user.c) */
void init_user_data(void);                               /* 初始化读者/管理员链表 + 初始管理员 */
bool register_user(char *name, char *pwd);               /* 注册读者, 返回是否成功 */
bool find_user(char *name, char *pwd, user **out);       /* 读者登录验证, 输出 user* */
bool find_admint(char *name, char *pwd, admint **out);   /* 管理员登录验证, 输出 admint* */
void show_all_users(void);                               /* 遍历打印所有读者 */
void destroy_user_data(void);                            /* 释放读者/管理员链表内存 */
void user_change_pwd(user *curuser, char *oldpwd);
void for_each_user_borrow_books(user *curuser);

#endif /* USER_H */

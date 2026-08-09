#ifndef USER_H
#define USER_H

#include "kernel.h"

/* 用户借阅记录的链表节点(随 user 一起管理) */
typedef struct mapnode
{
    char bookname[40];
    char author[20];
    struct mapnode *next;
} mapnode;

/* 读者 */
typedef struct {
    char userName[20];
    char password[20];
    mapnode *userborrow_list;   /* 该用户借阅的书籍链表 */
} user;

/* 管理员 */
typedef struct {
    char admintId[20];
    char password[20];
} admint;

/* 用户模块接口(实现在 user.c) */
void init_user_data(void);                               /* 初始化读者/管理员链表 + 初始管理员 */
bool register_user(char *name, char *pwd);               /* 注册读者, 返回是否成功 */
bool find_user(char *name, char *pwd, datanode **out);   /* 读者登录验证 */
bool find_admint(char *name, char *pwd, datanode **out); /* 管理员登录验证 */
void show_all_users(void);                               /* 遍历打印所有读者 */
void destroy_user_data(void);                            /* 释放读者/管理员链表内存 */

#endif /* USER_H */

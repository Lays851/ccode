#ifndef BORROW_H
#define BORROW_H

#include "user.h"

/* 借阅模块接口(实现在 borrow.c)
 * 借书/还书需要同时操作: 书籍库存(book模块) + 用户借阅链表(user结构体) */
void borrow_book(user *cur_user, char *bookname);  /* 借书: 库存-1, 加入用户借阅链表 */
void return_book(user *cur_user, char *bookname);  /* 还书: 库存+1, 从借阅链表删除 */
void brows_count(void);                            /* 管理员: 借阅统计(待实现) */

#endif /* BORROW_H */

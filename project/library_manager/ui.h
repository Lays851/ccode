#ifndef UI_H
#define UI_H

#include "kernel_list.h"
#include "user.h"

/* 菜单页面打印(实现在 ui.c) */
void homePage(void);
void loginPage(void);
void registerPage(void);
void userPage(void);
void admintPage(void);
void funcsetPage(void);

/* 菜单流程控制: 从 main.c 中拆出的各层菜单 */
void login_menu(void);              /* 二级: 登录菜单(管理员/读者) */
void admin_menu(void);              /* 三级: 管理员菜单 */
void user_menu(user *cur_user);     /* 三级: 读者菜单, 传入当前登录用户 */
void register_menu(void);           /* 注册流程 */

#endif /* UI_H */

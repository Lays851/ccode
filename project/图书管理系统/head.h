#ifndef HEAD_H
#define HEAD_H

#include "kernel.h"   /* 提供 bool / datanode 等类型定义, 修改: 原文件直接用这些类型但没有包含 */

/* 菜单页面函数(在 func.c 中实现) */
extern void homePage();
extern void loginPage();
extern void registerPage();
extern void userPage();
extern void admintPage();   /* 修改: 原写成 admitPage, 与 func.c 中的实现不一致 */
extern void funcsetPage();   /* 修改: 原缺分号, 导致整个头文件解析错乱, 连锁产生所有编译错误 */

/* 查找函数(在 main.c 中实现) */
// bool find(datanode *list, char *name, char *pwd,
//           bool (*equal)(void *, char *, char *), datanode **out);
// bool find_book(datanode *list, char *name,
//                bool (*equal)(void *, char *), datanode **out);

/* 待你实现 */
extern void brows_count();   /* 管理员: 借阅统计 */

#endif

/* user.c - 用户模块: 管理读者/管理员链表, 提供注册与登录验证
 * 模块化改造: 从 main.c 中拆分出来 */
#include "user.h"

static datanode *user_list = NULL;    /* 读者链表(模块私有) */
static datanode *admint_list = NULL;  /* 管理员链表(模块私有) */

/* 打印读者回调(仅本模块内部使用) */
static void usershow(void *tmp)
{
    user *u = (user *)tmp;
    printf("用户名称[%s]\n", u->userName);
}

/* 读者登录比较回调 */
static bool isRighUser(void *p, char *name, char *pwd)
{
    user *u = (user *)p;
    return strcmp(u->userName, name) == 0 && strcmp(u->password, pwd) == 0;
}

/* 管理员登录比较回调 */
static bool isRightadmint(void *p, char *name, char *pwd)
{
    admint *a = (admint *)p;
    return strcmp(a->admintId, name) == 0 && strcmp(a->password, pwd) == 0;
}

/* 通用查找: 遍历链表, 用 equal 回调判断是否匹配 */
static bool find(datanode *list, char *name, char *pwd,
                 bool (*equal)(void *, char *, char *), datanode **out)
{
    node *p = list->node.next;
    while (p != &list->node)
    {
        datanode *cur = (datanode *)((char *)p - (char *)&(((datanode *)0)->node));
        if (equal(cur->data, name, pwd))
        {
            *out = cur;
            return true;
        }
        p = p->next;
    }
    return false;
}

void init_user_data(void)
{
    user_list = init_datanode();
    admint_list = init_datanode();

    /* 添加初始管理员 */
    admint admintOne = {"Lay", "123456"};
    add_datanode(&admint_list->node, &new_datanode(&admintOne, sizeof(admint))->node);
}

bool register_user(char *name, char *pwd)
{
    user newuser;
    strcpy(newuser.userName, name);
    strcpy(newuser.password, pwd);
    newuser.userborrow_list = NULL;

    add_datanode(&user_list->node, &new_datanode(&newuser, sizeof(user))->node);
    return true;
}

bool find_user(char *name, char *pwd, datanode **out)
{
    return find(user_list, name, pwd, isRighUser, out);
}

bool find_admint(char *name, char *pwd, datanode **out)
{
    return find(admint_list, name, pwd, isRightadmint, out);
}

void show_all_users(void)
{
    for_each_node(&user_list->node, usershow);
}

void destroy_user_data(void)
{
    destroy_datanode(&user_list->node);
    destroy_datanode(&admint_list->node);
}

/* user.c - 用户模块: 管理读者/管理员链表, 提供注册与登录验证
 * 改造: 从 kernel.h(datanode 包装式) 换用 kernel_list.h(Linux 内核链表, 节点内嵌式) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user.h"

static LIST_HEAD(user_list);    /* 读者链表头(模块私有) */
static LIST_HEAD(admint_list);  /* 管理员链表头(模块私有) */

/* 打印一个读者 */
static void usershow(user *u)
{
    printf("用户名称[%s]\n", u->userName);
}

void init_user_data(void)
{
    /* 添加初始管理员 */
    admint *admintOne = malloc(sizeof(admint));
    if (admintOne == NULL)
        return;
    strcpy(admintOne->admintId, "Lay");
    strcpy(admintOne->password, "123456");
    list_add_tail(&admintOne->node, &admint_list);

    /* 读取读者信息 */
    FILE *fp = fopen ("user.txt", "r");
    while(1)
    {
        user *tmp = malloc(sizeof(user));
        if(fscanf(fp, "%s %s %d;", tmp->userName, tmp->password, &tmp->booksnum) == EOF)
        {
            free(tmp);
            break;
        }   
        fscanf(fp, "%*[^\n]");   // 跳过该行剩余字符
        fscanf(fp, "%*c");        // 跳过换行符 
        list_add_tail(&tmp->node, &user_list);
    }
    fclose(fp);
}

bool register_user(char *name, char *pwd)
{
    user *newuser = malloc(sizeof(user));
    if (newuser == NULL)
        return false;
    strcpy(newuser->userName, name);
    strcpy(newuser->password, pwd);
    newuser->booksnum = 0;
    newuser->userborrow_list = NULL;
    list_add_tail(&newuser->node, &user_list);
    return true;
}

bool find_user(char *name, char *pwd, user **out)
{
    user *pos;
    list_for_each_entry(pos, &user_list, node)
    {
        if (strcmp(pos->userName, name) == 0 && strcmp(pos->password, pwd) == 0)
        {
            *out = pos;
            return true;
        }
    }
    return false;
}

bool find_admint(char *name, char *pwd, admint **out)
{
    admint *pos;
    list_for_each_entry(pos, &admint_list, node)
    {
        if (strcmp(pos->admintId, name) == 0 && strcmp(pos->password, pwd) == 0)
        {
            *out = pos;
            return true;
        }
    }
    return false;
}

void show_all_users(void)
{
    user *pos;
    list_for_each_entry(pos, &user_list, node)
        usershow(pos);
}

void destroy_user_data(void)
{
    user *upos, *un;
    list_for_each_entry_safe(upos, un, &user_list, node)
    {
        list_del(&upos->node);
        free(upos);
    }

    admint *apos, *an;
    list_for_each_entry_safe(apos, an, &admint_list, node)
    {
        list_del(&apos->node);
        free(apos);
    }
}

void user_change_pwd(user *curuser, char *old)
{
    char tmp1[20], tmp2[20];
    if(strcmp(curuser->password, old) == 0)
    {
        while(1)
        {
        printf("请输入新密码："); scanf("%19s", tmp1); printf("\n");
        printf("请再次确认新密码："); scanf("%19s", tmp2);
        if(strcmp(tmp1, tmp2) == 0)
            break;
        else
            printf("两次输入不一致，请重新输入！\n");
        }

        strcpy(curuser->password, tmp1);
        printf("修改密码成功！\n");
    }
    else
        printf("原密码不正确！\n");
}

void for_each_user_borrow_books(user *curuser)
{
    mapnode *list = curuser->userborrow_list;
    if(list == NULL)
    {
        printf("你还没有借阅的书籍，快去找一本喜爱的书吧！\n");
        return;
    }

    printf("共借阅%d本书:", curuser->booksnum);
    while(list != NULL)
    {
        printf("%s\t", list->bookname);
        list = list->next;   
    }
    printf("\n");
}

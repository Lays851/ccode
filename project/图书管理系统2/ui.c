/* ui.c - 界面与菜单模块
 * 模块化改造: 原 func.c 的页面函数 + 原 main.c 中的菜单逻辑合并于此,
 * main.c 只负责初始化数据和主循环框架 */
#include "ui.h"
#include "book.h"
#include "borrow.h"

/* ============ 菜单页面打印 ============ */
void homePage()
{
    printf("====主菜单====\n");
    printf("1.登录\n");
    printf("2.注册\n");
    printf("3.访客浏览\n");
    printf("4.退出\n");
    printf("请输入操作（1 ~ 4）\n");
}

void loginPage()
{
    printf("====登录====\n");
    printf("1.管理员登录\n");
    printf("2.读者登录\n");
    printf("3.返回主菜单\n");
    printf("请输入操作（1 ~ 3）\n");
}

void registerPage()
{
    printf("====注册====\n");
    printf("1.读者注册\n");
    printf("2.返回主菜单\n");
    printf("请选择操作（1 ~ 2）\n");
}

void userPage()
{
    printf("====读者菜单====\n");
    printf("1.浏览所有图书\n");
    printf("2.借阅图书\n");
    printf("3.归还图书\n");
    printf("4.修改个人信息\n");
    printf("5.退出推出登录\n");
    printf("请输入操作（1 ~ 5）\n");
}

void admintPage()
{
    printf("====管理员菜单====\n");
    printf("1.读者信息\n");
    printf("2.图书信息\n");
    printf("3.增删改查图书信息\n");
    printf("4.借阅统计\n");
    printf("5.返回上一级\n");
    printf("请输入操作（1 ~ 5）\n");
}

void funcsetPage()
{
    printf("\n");
    printf("1.增添图书\n");
    printf("2.删除图书\n");
    printf("3.修改图书信息\n");
    printf("4.查找图书\n");
    printf("请输入要执行的操作\n");
}

/* ============ 菜单流程控制 ============ */

/* 二级菜单: 登录(管理员/读者) */
void login_menu(void)
{
    while (1)
    {
        int tmp;
        char name[20], pwd[20];

        loginPage();
        scanf("%d", &tmp);

        switch (tmp)
        {
        case 1: /* 管理员登录 */
            printf("请输入管理员用户名：");
            scanf("%19s", name);
            printf("\n请输入管理员密码：");
            scanf("%19s", pwd);
            printf("\n");

            datanode *thisadmint = NULL;
            if (find_admint(name, pwd, &thisadmint))
                admin_menu();
            else
                printf("账号或密码错误。\n");
            break;

        case 2: /* 读者登录 */
            printf("请输入用户名：");
            scanf("%19s", name);
            printf("\n请输入用户密码：");
            scanf("%19s", pwd);
            printf("\n");

            datanode *thisuser = NULL;
            if (find_user(name, pwd, &thisuser))
                user_menu((user *)thisuser->data);
            else
                printf("用户名或密码错误。\n");
            break;
        }

        if (tmp == 3)
            break;
    }
}

/* 三级菜单: 管理员操作 */
void admin_menu(void)
{
    while (1)
    {
        int n;
        admintPage();
        scanf("%d", &n);

        switch (n)
        {
        case 1:
            show_all_users();
            break;
        case 2:
            show_all_books();
            break;
        case 3: /* 增删改查图书信息 */
        {
            int n1, pri, mar;
            char curid[20], curname[40], curaut[20];

            funcsetPage();
            scanf("%d", &n1);

            switch (n1)
            {
            case 1: /* 增添 */
                printf("请依次输入书籍id，书名， 作者， 售价， 库存\n");
                scanf("%19s %39s %19s %d %d", curid, curname, curaut, &pri, &mar);
                add_book(curid, curname, curaut, pri, mar);
                printf("添加成功！\n");
                break;

            case 2: /* 删除 */
                printf("请输入要删除的书籍名称：\n");
                scanf("%39s", curname);
                if (del_book(curname))
                    printf("删除成功！\n");
                else
                    printf("未找到该书\n");
                break;

            case 3: /* 修改 */
                printf("请输入要修改的书籍名称：\n");
                scanf("%39s", curname);
                printf("请输入要修改的图书内容 1.名字 2.作者 3.价格\n");
                int n2;
                scanf("%d", &n2);
                if (n2 == 1)
                    printf("暂不允许修改书名\n");
                else if (n2 == 2)
                {
                    printf("请输入新作者名字\n");
                    scanf("%19s", curaut);
                    update_book_author(curname, curaut);
                    printf("更新成功！\n");
                }
                else if (n2 == 3)
                {
                    printf("请输入新价格\n");
                    double newprice;
                    scanf("%lf", &newprice);
                    update_book_price(curname, newprice);
                    printf("更新成功！\n");
                }
                else
                    printf("无效选项\n");
                break;

            case 4: /* 查找 */
                printf("请输入书名：\n");
                scanf("%39s", curname);
                search_book(curname);
                break;
            }
            break;
        }

        case 4:
            brows_count();   /* 借阅统计(待实现) */
            break;
        }

        if (n == 5)
            break;
    }
}

/* 三级菜单: 读者操作 */
void user_menu(user *cur_user)
{
    while (1)
    {
        int n;
        char bookname[40];

        userPage();
        scanf("%d", &n);

        switch (n)
        {
        case 1: /* 图书浏览 */
            show_all_books();
            break;
        case 2: /* 借阅图书 */
            printf("请输入要借阅的书籍名称：");
            scanf("%39s", bookname);
            borrow_book(cur_user, bookname);
            break;
        case 3: /* 归还图书 */
            printf("请输入要归还的书籍名字：");
            scanf("%39s", bookname);
            return_book(cur_user, bookname);
            break;
        case 4:
            printf("功能开发中。。。。\n");   /* 修改个人信息(待实现) */
            break;
        }

        if (n == 5)
            break;
    }
}

/* 注册流程 */
void register_menu(void)
{
    int tmp;
    char name[20], pwd[20];

    registerPage();
    scanf("%d", &tmp);

    if (tmp == 1)
    {
        printf("注册，请输入你的用户名：");
        scanf("%19s", name);
        printf("\n     请输入你的密码：");
        scanf("%19s", pwd);
        printf("\n");

        register_user(name, pwd);
        printf("注册成功！\n");
    }
}

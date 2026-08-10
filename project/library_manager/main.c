/* main.c - 程序入口与整体框架
 * 模块化改造: 从原 449 行瘦身到 40 行左右,
 * 只负责: 初始化各模块数据 + 主菜单循环, 具体逻辑都在对应模块中
 * 编译: gcc main.c book.c user.c borrow.c ui.c -o book (kernel_list.h 纯头文件, 无需 kernel.c) */
#include <stdio.h>
#include "head.h"

int main(void)
{
    /* 初始化各模块数据 */
    
    init_user_data();
    init_book_data();

    printf("欢迎来到傅诚图书馆\n");

    /* 主循环: 整体框架 */
    while (1)
    {
        homePage();
        int n;
        while(scanf("%d", &n) != 1 || n < 1 || n > 4)
        {
            printf("输入不合法请重新输入！\n");
            while(getchar() != '\n');
        }
        printf("%d",n);

        switch (n)
        {
        case 1:
            login_menu();          /* 登录(ui.c) */
            break;
        case 2:
            register_menu();       /* 注册(ui.c) */
            break;
        case 3:
            show_all_books();      /* 访客浏览(book.c) */
            break;
        case 4:
            /* 退出前释放各模块链表的内存 */
            destroy_book_data();
            destroy_user_data();
            return 0;
        }
    }
}

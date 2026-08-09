#include "kernel.h"   

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

void  registerPage()
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

void brows_count()
{
    printf("功能开发中。。。\n");
}
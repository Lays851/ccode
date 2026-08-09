#include "kernel.h"
#include "head.h"

typedef struct {
    char bookid[20];
    char bookname[40];   /* 修改: 原为 bookname[20], 但《linux环境编程图文指南》这类书名超过20字节,
                          * 初始化时会被截断, 加大到40 */
    char author[20];
    double price;
    int margin;
}book;

typedef struct {
    char admintId[20];
    char password[20];
}admint;

typedef struct book_map
{
    char bookname[40]; 
    char author[20];
    struct book_map *next;
}mapnode;

typedef struct {
    char userName[20];
    char password[20];
    mapnode *userborrow_list;   // 指向该用户借阅书籍链表的指针(借阅记录用, 待实现)
}user;

mapnode * mapping(book *ori)
{
    mapnode *map = calloc(1, sizeof(mapnode));
    if(map == NULL)
        return NULL;

    strcpy(map->bookname, ori->bookname);
    strcpy(map->author, ori->author);
    map->next = NULL;

    return map;
}

mapnode * add_mapnode(mapnode *head, mapnode *new)
/* 修改: 原实现 head->next = new 会覆盖链表上已挂好的后续节点
 * (借第三本书时第二本的记录会丢失), 应遍历到链表尾部再挂接;
 * 另外增加了 new 为 NULL 的保护 */
{
    if (new == NULL)
        return head;
    if (head == NULL)
        return new;

    mapnode *tmp = head;
    while (tmp->next != NULL)
        tmp = tmp->next;
    tmp->next = new;
    return head;
}

mapnode * del_mapnode(mapnode *head, char *name)
/* 修改: 原代码 maonode 拼写错误(编译不过, 应为 mapnode);
 * 删除节点时没有 free 释放内存, 造成内存泄漏, 已补上 */
{
    if (head == NULL)
        return NULL;

    if (strcmp(head->bookname, name) == 0)   // 要删除的是头节点
    {
        mapnode *next = head->next;
        free(head);
        return next;
    }

    mapnode *tmp = head;
    mapnode *p = head->next;
    while (p != NULL)
    {
        if (strcmp(p->bookname, name) == 0)
        {
            tmp->next = p->next;
            free(p);   /* 修改: 原代码漏掉 free, 节点内存泄漏 */
            return head;
        }
        tmp = p;
        p = p->next;
    }

    return head;
}

/* ============ 打印函数(供 for_each_node 遍历时回调) ============ */
void bookshow(void *tmp)
/* 修改: 参数类型由 book* 改为 void*, 因为 for_each_node 的回调类型是 void(*)(void*) */
{
    book *b = (book *)tmp;
    printf("书籍编号[%s], 书名《%s》, 作者：%s, 价格：%.1f, 库存：%d\n",
           b->bookid, b->bookname, b->author, b->price, b->margin);
}

void usershow(void *tmp)
/* 修改: 参数类型由 book* 改为 user*(原来是 book* 却访问用户字段), 并改为 void* */
{
    user *u = (user *)tmp;
    printf("用户名称[%s]\n", u->userName);
    /* 修改: 原 uaerName 拼写错误, 应为 userName */
}

/* ============ 登录/查找的相等判断函数 ============ */
bool isRighUser(void *p, char *name, char *pwd)
/* 修改: 参数改为 void* 以便与函数指针类型匹配;
 * 原 p1->password 中 p1 未定义(应为 p);
 * 字符串用 == 比较是错误的(比较的是地址不是内容), 必须用 strcmp */
{
    user *u = (user *)p;
    return strcmp(u->userName, name) == 0 && strcmp(u->password, pwd) == 0;
}

bool isequalbook(const void *p1, const void *p2)
/* 修改: 参数类型改为 const void*, 与 kernel.h 中 del_datanode 要求的
 * 回调类型 bool (*)(const void *, const void *) 一致;
 * bookid 是字符串, == 比较的是地址, 应改用 strcmp */
{
    const book *tmp1 = (const book *)p1;
    const book *tmp2 = (const book *)p2;

    return strcmp(tmp1->bookid, tmp2->bookid) == 0;
}

bool isRightadmint(void *p, char *name, char *pwd)
/* 修改: 字符串比较 == 改为 strcmp; 参数改为 void* */
{
    admint *a = (admint *)p;
    return strcmp(a->admintId, name) == 0 && strcmp(a->password, pwd) == 0;
}

bool isRightbook(void *p, char *name)
/* 修改: 字符串比较 == 改为 strcmp; 参数改为 void* */
{
    book *b = (book *)p;
    return strcmp(b->bookname, name) == 0;
}

/* ============ 通用查找: 按 用户名+密码 登录验证 ============ */
bool find(datanode *list, char *name, char *pwd,
          bool (*equal)(void *, char *, char *), datanode **out)
/* 修改: 原实现有多个致命错误(局部变量 tmp 与参数 tmp 重名、return bool 等),
 * 已重写; 原 findPerson 与 find 功能重复且未被调用, 已删除, 正确实现合并于此 */
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

/* ============ 按 书名 查找书籍 ============ */
bool find_book(datanode *list, char *name,
               bool (*equal)(void *, char *), datanode **out)
/* 新增: 借书/还书功能需要按书名查找, 原代码调用了未定义的 find_book */
{
    node *p = list->node.next;
    while (p != &list->node)
    {
        datanode *cur = (datanode *)((char *)p - (char *)&(((datanode *)0)->node));
        if (equal(cur->data, name))
        {
            *out = cur;
            return true;
        }
        p = p->next;
    }
    return false;
}

int main(void)
{
    datanode *user_list = init_datanode();
    datanode *admint_list = init_datanode();
    datanode *book_list = init_datanode();

    //添加初始管理员
    admint admintOne = {"Lay", "123456"};
    datanode *admintOne_node = new_datanode(&admintOne, sizeof(admint));
    add_datanode(&admint_list->node, &admintOne_node->node);

    //添加初始书籍
    book book1 = {"book001", "老人与海", "海明威", 30, 8};
    book book2 = {"book002", "linux环境编程图文指南", "林世霖", 20.5, 4};
    book book3 = {"book003", "语文书", "大刷个", 39.2, 2};
    /* 修改: 原第三本误写成 book book1 = {...}(变量重复声明), 应为 book3 */

    datanode *bookOne_node = new_datanode(&book1, sizeof(book));
    datanode *bookTwo_node = new_datanode(&book2, sizeof(book));
    datanode *bookThi_node = new_datanode(&book3, sizeof(book));
    /* 修改: 原 new_datanode(&book3, ...) 中 book3 未定义, 已修正声明 */

    add_datanode(&book_list->node, &bookOne_node->node);
    add_datanode(&book_list->node, &bookTwo_node->node);
    add_datanode(&book_list->node, &bookThi_node->node);

    //系统初始化与首页
    printf("欢迎来到傅诚图书馆\n");

    //根据用户输入执行
    while(1)
    {
        //一级桌面
        homePage();
        int n;
        scanf("%d", &n);
        switch(n)
        {
        case 1://登录
            while(1){
                int tmp;
                char name[20];
                char pwd[20];
                //二级桌面
                loginPage();
                scanf("%d", &tmp);

                switch(tmp)
                {
                case 1://管理员登录
                    //管理员登录，验证管理员
                    printf("请输入管理员用户名：");
                    scanf("%19s", name);
                    printf("\n");
                    printf("请输入管理员密码：");
                    scanf("%19s", pwd);
                    printf("\n");

                    datanode *thisadmint = NULL;
                    if(find(admint_list, name, pwd, isRightadmint, &thisadmint))
                    {
                        while(1){//三级桌面
                            int n;
                            admintPage();
                            scanf("%d", &n);

                            switch(n)
                            {
                            case 1://遍历读者
                                for_each_node(&user_list->node, usershow);
                                break;
                            case 2://遍历书籍
                                for_each_node(&book_list->node, bookshow);
                                break;
                            case 3: //增删改查图书信息
                                int n1, mar;
                                double pri;
                                char curid[20], curname[40], curaut[20];
                                /* 修改: curname 加大到 40, 与书籍结构体 bookname[40] 一致 */
                                datanode *target = NULL;
                                funcsetPage();   /* 修改: 原调用 funcset(), 但实现和声明都是 funcsetPage(), 名字不一致 */
                                scanf("%d",&n1);
                                
                                switch(n1)   /* 修改: swich 拼写错误; 原多了分号导致 switch 失效 */
                                {
                                case 1:
                                    printf ("请依次输入书籍id，书名， 作者， 售价， 库存\n");
                                    scanf ("%19s %39s %19s %lf %d", curid, curname, curaut, &pri, &mar);
                                    /* 修改: %s 加宽度限制, 防止输入超长覆盖内存 */
                                    book booktmp;   /* 修改: 原 book *booktmp = {curid, curname, curaut, &pri, &mar}
                                                     * 是指针配初始化列表, 且 &pri/&mar 传的是地址, 均为错误;
                                                     * 应定义结构体变量再逐字段赋值 */
                                    strcpy(booktmp.bookid, curid);
                                    strcpy(booktmp.bookname, curname);
                                    strcpy(booktmp.author, curaut);
                                    booktmp.price = pri;
                                    booktmp.margin = mar;
                                    add_datanode(&book_list->node,
                                                 &new_datanode(&booktmp, sizeof(book))->node);
                                    /* 修改: 原 add_datanode 第一个参数应传 &book_list->node(node*), 不是 book_list;
                                     * 第二个参数应取 new_datanode 返回值的 ->node 成员 */
                                    break;
                                case 2:
                                    printf("请输入要删除的书籍名称：\n");   /* 修改: pintf -> printf */
                                    scanf("%39s", curname);
                                    if (find_book(book_list, curname, isRightbook, &target))
                                        /* 修改: 原 find_book 后未判断就直接用 target->data, 找不到书时 target 为空会崩溃 */
                                    {
                                        if (del_datanode(&book_list->node, target->data, isequalbook))
                                            printf("删除成功！\n");
                                        else
                                            printf("删除失败！\n");
                                    }
                                    else
                                        printf("未找到该书\n");
                                    break;   /* 修改: 原缺少 break, 会直接落入 case 3(fall-through) */

                                case 3:
                                    printf("请输入要修改的书籍名称：\n");
                                    scanf("%39s", curname);
                                    /* 修改: 原代码直接使用上一次输入残留的 curname, 无法指定要改的书 */
                                    if (!find_book(book_list, curname, isRightbook, &target))
                                    {
                                        printf("未找到该书\n");
                                        break;
                                    }
                                    printf("请输入要修改的图书内容 1.名字 2.作者 3.价格\n");   /* 修改: pritnf -> printf */
                                    int n2; scanf("%d", &n2);
                                    if(n2 == 1)
                                        printf("暂不允许修改书名\n");
                                    else if(n2 == 2)
                                    {
                                        /* 修改: 原 else if(n2 == 2){} 是空块, 后面的语句变成无条件执行 */
                                        printf("请输入新作者名字\n"); scanf("%19s", curaut);
                                        strcpy(((book *)target->data)->author, curaut);
                                        /* 修改: 原用 memcpy(..., sizeof(curaut)) 会连未初始化字节一起拷入, strcpy 更合适 */
                                        printf("更新成功！\n");
                                    }
                                    else if(n2 == 3)
                                    {
                                        printf("请输入新价格\n");
                                        scanf("%lf", &pri);
                                        /* 修改: 原 curpri 未声明, 且 char* 赋给 double 是类型错误 */
                                        ((book *)target->data)->price = pri;
                                        printf("更新成功！\n");
                                    }
                                    else
                                        printf("无效选项\n");
                                    break;
                                case 4:
                                    printf("请输入书名：\n"); scanf("%39s", curname);
                                    if (find_book(book_list, curname, isRightbook, &target))
                                        bookshow(target->data);
                                        /* 修改: 原未判断查找结果, 找不到书时 target 为空会崩溃 */
                                    else
                                        printf("未找到该书\n");
                                    break;
                                }
                                
                               
                                break;
                            case 4:
                                brows_count();   // 待实现: 借阅统计
                                break;
                            }
                            if(n == 5)
                                break;
                        }

                    }
                    else
                        printf("账号或密码错误。\n");

                    break;
                case 2://用户登录 验证用户
                    printf("请输入用户名：");
                    scanf("%19s", name);
                    printf("\n");
                    printf("请输入用户密码：");
                    scanf("%19s", pwd);
                    printf("\n");

                    datanode *thisuser = NULL, *book_node = NULL;
                    /* 修改: 原 thisuser 在 if 内部才声明, 但 if 的条件里已经使用 &thisuser,
                     * 作用域错误(变量在使用前不存在), 提前到 if 之前声明
                     * 另: 变量原名 book 与类型名 book 重名, 导致 (book *) 强转无法解析,
                     * 改名为 book_node */
                    if(find(user_list, name, pwd, isRighUser, &thisuser))
                    {
                        while(1)
                        {
                            int n;
                            char bookname[40];   /* 修改: 原为 [20], 与书籍结构体 bookname[40] 不一致,
                                                  * 长书名会被截断导致查找失败 */
                            userPage();
                            scanf("%d", &n);

                            switch(n)
                            {
                            case 1://图书浏览
                                for_each_node(&book_list->node, bookshow);
                                /* 修改: 原用未定义的 show, 应使用已实现的 bookshow */
                                break;
                            case 2://借阅图书
                                printf("请输入要借阅的书籍名称：");
                                scanf("%39s", bookname);
                                if (find_book(book_list, bookname, isRightbook, &book_node)
                                    && ((book *)book_node->data)->margin != 0)
                                    /* 修改: 原 find_book 未定义; book->data 是 void* 不能直接 -> 访问成员,
                                     * 需要 (book *) 强转; if 后面误加了分号, 导致判断失效且代码块无条件执行 */
                                {
                                    ((book *)(book_node->data))->margin--;   // 库存减一
                                    printf("借阅成功！\n");
                                    mapnode *bookmaping = mapping((book *)(book_node->data));
                                    user *cur_user = (user *)thisuser->data;
                                    /* 修改: thisuser->data 是 void*, 不能直接 -> 访问成员,
                                     * 先强转为 user* 再操作 */
                                    cur_user->userborrow_list = add_mapnode(cur_user->userborrow_list, bookmaping);
                                }
                                else
                                {
                                    printf("未找到该书或库存不足\n");
                                }
                                break;
                            case 3://归还图书
                                printf("请输入要归还的书籍名字：");
                                scanf("%39s", bookname);
                                if (find_book(book_list, bookname, isRightbook, &book_node))
                                    /* 修改: 原 return_book 未定义, 且 (return_book(...)) { } 不是合法的语句结构 */
                                {
                                    ((book *)book_node->data)->margin++;  // 库存加一
                                    printf("归还成功！\n");
                                    user *cur_user = (user *)thisuser->data;
                                    /* 修改: 同上, void* 需要强转为 user* 再操作 */
                                    cur_user->userborrow_list = del_mapnode(cur_user->userborrow_list, bookname);
                                }
                                else
                                {
                                    printf("未找到该书\n");
                                }
                                break;
                            case 4:
                                printf("功能开发中。。。。\n");   /* 修改: 补上缺失的分号 */
                                break;
                            }

                            if(n == 5)
                                break;

                        }
                    }
                    else
                        printf("用户名或密码错误。");

                    break;
                }
                if(tmp == 3)
                    break;
            }
            break;

        case 2://注册
            int tmp;
            char name[20], pwd[20];
            registerPage();
            scanf("%d", &tmp);

            if(tmp == 1)
            {
                printf("注册，请输入你的用户名：");   /* 修改: 补上缺失的分号 */
                scanf("%19s", name); printf("\n");
                printf("     请输入你的密码：");      /* 修改: 补上缺失的分号 */
                scanf("%19s", pwd); printf("\n");

                user newuser;   /* 修改: 原 {name, pwd, NULL} 用数组名初始化结构体成员是编译错误,
                                 * C 语言数组不能在结构体初始化时直接赋值, 改用 strcpy */
                strcpy(newuser.userName, name);
                strcpy(newuser.password, pwd);
                newuser.userborrow_list = NULL;
                add_datanode(&user_list->node,
                             &new_datanode(&newuser, sizeof(newuser))->node);
                printf("注册成功！\n");
            }  /* 修改: esle -> else */
            
            break;
        case 3://访客浏览
            //遍历图书目录
            for_each_node(&book_list->node, bookshow);   /* 修改: 补上缺失的分号 */
            break;

        case 4://退出
            //退出前释放三个链表占用的内存, 避免内存泄漏
            destroy_datanode(&user_list->node);
            destroy_datanode(&admint_list->node);
            destroy_datanode(&book_list->node);
            return 0;
            break;
        }

    }
}

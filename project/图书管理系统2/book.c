/* book.c - 书籍模块: 管理书籍链表与书籍的增删改查
 * 模块化改造: 从 main.c 中拆分出来, 书籍链表只在本文件可见 */
#include "book.h"

static datanode *book_list = NULL;   /* 书籍链表(模块私有) */

/* 打印回调(仅本模块内部使用) */
static void bookshow(void *tmp)
{
    book *b = (book *)tmp;
    printf("书籍编号[%s], 书名《%s》, 作者：%s, 价格：%.1f, 库存：%d\n",
           b->bookid, b->bookname, b->author, b->price, b->margin);
}

/* 书名比较回调 */
static bool isRightbook(void *p, char *name)
{
    book *b = (book *)p;
    return strcmp(b->bookname, name) == 0;
}

/* 按 bookid 比较(del_datanode 的回调, 删除时按编号精确定位) */
static bool isequalbook(const void *p1, const void *p2)
{
    const book *b1 = (const book *)p1;
    const book *b2 = (const book *)p2;
    return strcmp(b1->bookid, b2->bookid) == 0;
}

void init_book_data(void)
{
    book_list = init_datanode();

    book book1 = {"book001", "老人与海", "海明威", 30, 8};
    book book2 = {"book002", "linux环境编程图文指南", "林世霖", 20.5, 4};
    book book3 = {"book003", "语文书", "大刷个", 39.2, 2};

    add_datanode(&book_list->node, &new_datanode(&book1, sizeof(book))->node);
    add_datanode(&book_list->node, &new_datanode(&book2, sizeof(book))->node);
    add_datanode(&book_list->node, &new_datanode(&book3, sizeof(book))->node);
}

void show_all_books(void)
{
    for_each_node(&book_list->node, bookshow);
}

bool find_book(char *name, datanode **out)
{
    node *p = book_list->node.next;
    while (p != &book_list->node)
    {
        datanode *cur = (datanode *)((char *)p - (char *)&(((datanode *)0)->node));
        if (isRightbook(cur->data, name))
        {
            *out = cur;
            return true;
        }
        p = p->next;
    }
    return false;
}

void add_book(char *id, char *name, char *author, double price, int margin)
{
    book newbook;
    strcpy(newbook.bookid, id);
    strcpy(newbook.bookname, name);
    strcpy(newbook.author, author);
    newbook.price = price;
    newbook.margin = margin;

    add_datanode(&book_list->node, &new_datanode(&newbook, sizeof(book))->node);
}

bool del_book(char *name)
{
    datanode *target = NULL;
    if (!find_book(name, &target))
        return false;
    return del_datanode(&book_list->node, target->data, isequalbook);
}

void update_book_author(char *name, char *author)
{
    datanode *target = NULL;
    if (find_book(name, &target))
        strcpy(((book *)target->data)->author, author);
}

void update_book_price(char *name, double price)
{
    datanode *target = NULL;
    if (find_book(name, &target))
        ((book *)target->data)->price = price;
}

void search_book(char *name)
{
    datanode *target = NULL;
    if (find_book(name, &target))
        bookshow(target->data);
    else
        printf("未找到该书\n");
}

void destroy_book_data(void)
{
    destroy_datanode(&book_list->node);
}

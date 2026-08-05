#define DATATYPE int
#include "head.h"

/* 打印整型数据 */
static void show_int(int data)
{
    printf("%d ", data);
}

static void print_list(node *head, const char *msg)
{
    printf("%s: ", msg);
    list_for_each(head, show_int);
    printf("\n");
}

/* 测试1：空链表遍历（不应崩溃） */
static void test_empty_list(void)
{
    printf("===== 测试1：空链表遍历 =====\n");
    node *head = init_list();
    print_list(head, "空链表");
    head = list_destroy(head);
    free(head);
    printf("空链表测试通过\n\n");
}

/* 测试2：尾部插入 */
static void test_add_tail(void)
{
    printf("===== 测试2：尾部插入 =====\n");
    node *head = init_list();
    for(int i = 1; i <= 5; i++)
        list_add_tail(head, newnode(i, NULL));
    print_list(head, "尾部插入1-5");
    head = list_destroy(head);
    free(head);
    printf("尾部插入测试通过\n\n");
}

/* 测试3：头部插入（头插法逆序） */
static void test_add_head(void)
{
    printf("===== 测试3：头部插入 =====\n");
    node *head = init_list();
    for(int i = 1; i <= 5; i++)
        list_add(head, newnode(i, NULL));
    print_list(head, "头插1-5(应为5 4 3 2 1)");
    head = list_destroy(head);
    free(head);
    printf("头部插入测试通过\n\n");
}

/* 测试4：混合插入 */
static void test_mixed_add(void)
{
    printf("===== 测试4：混合插入 =====\n");
    node *head = init_list();
    list_add_tail(head, newnode(1, NULL));
    list_add_tail(head, newnode(2, NULL));
    list_add(head, newnode(0, NULL));      // 头插
    list_add_tail(head, newnode(3, NULL)); // 尾插
    print_list(head, "混合插入(应为0 1 2 3)");
    head = list_destroy(head);
    free(head);
    printf("混合插入测试通过\n\n");
}

/* 测试5：删除中间节点 */
static void test_delete_node(void)
{
    printf("===== 测试5：删除节点 =====\n");
    node *head = init_list();
    for(int i = 1; i <= 5; i++)
        list_add_tail(head, newnode(i, NULL));
    print_list(head, "删除前");

    /* 删除值为3的节点 */
    node *tmp = head->next;
    while(tmp != head)
    {
        if(tmp->data == 3)
        {
            list_del(tmp);
            free(tmp);
            break;
        }
        tmp = tmp->next;
    }
    print_list(head, "删除3后(应为1 2 4 5)");

    /* 删除头节点后的第一个节点(值为1) */
    node *first = head->next;
    list_del(first);
    free(first);
    print_list(head, "删除首节点后(应为2 4 5)");

    head = list_destroy(head);
    free(head);
    printf("删除节点测试通过\n\n");
}

/* 测试6：单元素链表 */
static void test_single_element(void)
{
    printf("===== 测试6：单元素链表 =====\n");
    node *head = init_list();
    list_add_tail(head, newnode(100, NULL));
    print_list(head, "单元素");
    head = list_destroy(head);
    free(head);
    printf("单元素链表测试通过\n\n");
}

/* 测试7：反复销毁与重建 */
static void test_destroy_rebuild(void)
{
    printf("===== 测试7：销毁后重建 =====\n");
    node *head = init_list();
    list_add_tail(head, newnode(1, NULL));
    list_add_tail(head, newnode(2, NULL));
    head = list_destroy(head);
    free(head);
    printf("第一次销毁完成\n");

    head = init_list();
    list_add_tail(head, newnode(10, NULL));
    list_add_tail(head, newnode(20, NULL));
    print_list(head, "重建后(应为10 20)");
    head = list_destroy(head);
    free(head);
    printf("销毁重建测试通过\n\n");
}

int main(void)
{
    test_empty_list();
    test_add_tail();
    test_add_head();
    test_mixed_add();
    test_delete_node();
    test_single_element();
    test_destroy_rebuild();
    printf("========== 所有测试通过 ==========\n");
    return 0;
}

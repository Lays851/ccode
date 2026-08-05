#include <string.h>
#define DATATYPE char*
#include "head.h"

/* 打印字符串 */
static void show_str(char *data)
{
    printf("[%s] ", data);
}

static void print_list(node *head, const char *msg)
{
    printf("%s: ", msg);
    list_for_each(head, show_str);
    printf("\n");
}

/* 测试1：字符串字面量插入（浅拷贝，适用于字面量） */
static void test_string_literal(void)
{
    printf("===== 测试1：字符串字面量 =====\n");
    node *head = init_list();
    list_add_tail(head, newnode("hello", NULL));
    list_add_tail(head, newnode("world", NULL));
    list_add_tail(head, newnode("generic", NULL));
    list_add_tail(head, newnode("list", NULL));
    print_list(head, "字符串链表");
    head = list_destroy(head);
    free(head);
    printf("字符串字面量测试通过\n\n");
}

/* 测试2：头插法逆序 */
static void test_string_head_insert(void)
{
    printf("===== 测试2：头插法 =====\n");
    node *head = init_list();
    list_add(head, newnode("A", NULL));
    list_add(head, newnode("B", NULL));
    list_add(head, newnode("C", NULL));
    print_list(head, "头插A,B,C(应为C B A)");
    head = list_destroy(head);
    free(head);
    printf("头插法测试通过\n\n");
}

/* 测试3：删除指定字符串 */
static void test_string_delete(void)
{
    printf("===== 测试3：删除字符串 =====\n");
    node *head = init_list();
    list_add_tail(head, newnode("apple", NULL));
    list_add_tail(head, newnode("banana", NULL));
    list_add_tail(head, newnode("cherry", NULL));
    list_add_tail(head, newnode("date", NULL));
    print_list(head, "删除前");

    /* 删除 banana */
    node *tmp = head->next;
    while(tmp != head)
    {
        if(strcmp(tmp->data, "banana") == 0)
        {
            list_del(tmp);
            free(tmp);
            break;
        }
        tmp = tmp->next;
    }
    print_list(head, "删除banana后");

    head = list_destroy(head);
    free(head);
    printf("删除字符串测试通过\n\n");
}

/* 测试4：空链表与单元素 */
static void test_string_edge(void)
{
    printf("===== 测试4：边界情况 =====\n");
    node *head = init_list();
    print_list(head, "空链表");

    list_add_tail(head, newnode("only", NULL));
    print_list(head, "单元素");

    head = list_destroy(head);
    free(head);
    printf("边界情况测试通过\n\n");
}

int main(void)
{
    test_string_literal();
    test_string_head_insert();
    test_string_delete();
    test_string_edge();
    printf("========== 所有字符串测试通过 ==========\n");
    return 0;
}

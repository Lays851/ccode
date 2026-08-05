#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 20

typedef int datatype;

/* 双向链表节点：prev 指向前驱(向头方向)，next 指向后继(向尾方向) */
struct node
{
    datatype data;
    struct node *prev;
    struct node *next;
};

typedef struct
{
    unsigned long table_size;
    struct node **table_entry;   /* 每个桶存头节点指针；&table_entry[i] 即二级指针 */
} hash_table;

hash_table *init_ht(unsigned long size)
{
    hash_table *ht = malloc(sizeof(hash_table));
    if (ht == NULL) return NULL;

    ht->table_size = size;
    ht->table_entry = calloc(size, sizeof(struct node *));
    return ht;
}

/* 尾插：二级指针 pp 指向"链接位置"（表头指针或某节点 next 域），空桶/非空桶统一处理 */
void hash_add(datatype data, hash_table *ht)
{
    unsigned long pos = data % (SIZE - 1);

    struct node *new = malloc(sizeof(struct node));
    if (new == NULL) return;
    new->data = data;
    new->next = NULL;

    struct node **pp = &ht->table_entry[pos];
    struct node *prev = NULL;

    while (*pp != NULL)          /* 走到链表末尾 */
    {
        prev = *pp;
        pp = &(*pp)->next;
    }

    new->prev = prev;            /* 挂好前驱 */
    *pp = new;                   /* 挂接到桶尾 */
}

/* 删除：二级指针直接绕过被删节点，删除头节点也无需特判 */
bool hash_delete(datatype data, hash_table *ht)
{
    unsigned long pos = data % (SIZE - 1);
    struct node **pp = &ht->table_entry[pos];

    while (*pp != NULL)
    {
        if ((*pp)->data == data)
        {
            struct node *victim = *pp;
            if (victim->next != NULL)
                victim->next->prev = victim->prev;   /* 修复后继的 prev */
            *pp = victim->next;                      /* 绕过被删节点 */
            free(victim);
            return true;
        }
        pp = &(*pp)->next;
    }
    return false;
}

/* 查找：返回所在桶下标 */
int hash_find(datatype data, hash_table *ht)
{
    unsigned long pos = data % (SIZE - 1);
    struct node *p = ht->table_entry[pos];

    while (p != NULL)
    {
        if (p->data == data)
            return pos;
        p = p->next;
    }
    return -1;
}

/* 正向遍历（头 → 尾） */
void show(hash_table *ht)
{
    for (unsigned long i = 0; i < ht->table_size; i++)
    {
        printf("table_entry[%lu]: ", i);
        struct node *p = ht->table_entry[i];
        while (p != NULL)
        {
            printf("%d\t", p->data);
            p = p->next;
        }
        printf("\n");
    }
}

/* 反向遍历（尾 → 头），体现 prev 的价值 */
void show_reverse(hash_table *ht)
{
    for (unsigned long i = 0; i < ht->table_size; i++)
    {
        printf("table_entry[%lu]: ", i);
        struct node *p = ht->table_entry[i];
        if (p == NULL) { printf("\n"); continue; }

        while (p->next != NULL)   /* 先走到尾部 */
            p = p->next;
        while (p != NULL)         /* 借 prev 向前遍历 */
        {
            printf("%d\t", p->data);
            p = p->prev;
        }
        printf("\n");
    }
}

int main(void)
{
    hash_table *ht = init_ht(SIZE);

    srand(time(NULL));
    for (int i = 0; i < 10; i++)
        hash_add(rand() % 1000, ht);

    printf("=== 正向遍历 ===\n");
    show(ht);

    printf("\n=== 反向遍历 ===\n");
    show_reverse(ht);

    int n;
    printf("\n输入要查找的数据(负数退出): ");
    while (scanf("%d", &n) == 1 && n >= 0)
    {
        int pos = hash_find(n, ht);
        if (pos == -1)
            printf("未找到 %d\n", n);
        else
        {
            printf("找到 %d，位于 table_entry[%d]，已删除\n", n, pos);
            hash_delete(n, ht);
            show(ht);
        }
        printf("输入要查找的数据(负数退出): ");
    }

    return 0;
}

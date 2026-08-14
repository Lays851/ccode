// git 练习程序:打印一个链表
// 今天的目的不是算法,是熟悉 git 的 add -> commit -> push 流程
#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} Node;

int main(void) {
    Node *head = NULL;
    for (int i = 1; i <= 5; i++) {
        Node *p = malloc(sizeof(Node));
        p->data = i;
        p->next = head;
        head = p;
    }
    for (Node *p = head; p; p = p->next)
        printf("%d ", p->data);
    printf("\n");

    int s[] = {0};
    s[1] = 1;
    printf("%ld\n", sizeof(s));
    return 0;
}

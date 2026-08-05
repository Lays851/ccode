struct student
{
    char *name;
    int age;
};
#define DATATYPE struct student

#include "head.h"

void show(struct student stu)
{
    printf("姓名:%s 年龄:%d\n", stu.name, stu.age);
}

void release_data(struct student *stu)
{
    free(stu->name);
}



int main(void)
{
    node *head = init_list(); 
    struct student jack = {"jack", 18};
    struct student jill = {"jill", 19};
    struct student mary = {"fuchen", 20};
    jack.name = malloc(100);
    strcpy(jack.name, "jack");
    jill.name = malloc(100);
    strcpy(jill.name, "jill");
    mary.name = malloc(100);
    strcpy(mary.name, "fuchen");
    
    list_add_tail(head, newnode(jack, NULL));
    list_add_tail(head, newnode(jill, NULL));
    list_add_tail(head, newnode(mary, NULL));

    list_for_each(head, show);
    head = list_destroy(head, release_data);
    free(head);
    printf("链表已销毁\n");

    return 0;
}
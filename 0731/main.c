#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "kernel_list.h"

typedef struct student
{
    char *name;
    int age;
    struct list_head node;
} student;

student *init_student()
{
    student *stu = malloc(sizeof(student));
    if (stu == NULL)
        return NULL;
    
    INIT_LIST_HEAD(&stu->node);

    return stu;
}

student *new_student(char *name, int age)
{
    student *stu = malloc(sizeof(student));
    if (stu == NULL)
    {
        return NULL;
    }

    stu->name = malloc(100);
    strcpy(stu->name, name);
    stu->age = age;

    INIT_LIST_HEAD(&stu->node);
    return stu;
}

void show(student *stu)
{
    if (list_empty(&stu->node))
        return;

    struct list_head *listnode;
    list_for_each(listnode, &stu->node)
    {
        student *pos = list_entry(listnode, student, node);
        printf("姓名:%s 年龄:%d\n", pos->name, pos->age);
    }
    printf("\n");
}

void destroy_list(student *stu)
{
    if (list_empty(&stu->node))
        return;

    struct list_head *listnode;
    struct list_head *n;

    list_for_each_safe(listnode, n, &stu->node)
    {
        student *pos = list_entry(listnode, student, node);
        list_del_init(&pos->node);
        free(pos->name);
        free(pos);
    }

}


int main(void)
{
    student *stu = init_student();
    if (stu != NULL)
        printf("初始化成功\n");
    else
        perror("初始化失败\n");

    student *jack = new_student("jack", 18);
    student *mary = new_student("mary", 80);
    student *jill = new_student("jill", 19);
    student *fuchen = new_student("fuchen", 20);
    student *james = new_student("james", 21);
    student *bill = new_student("bill", 22);

    list_add_tail(&jack->node, &stu->node);
    list_add_tail(&mary->node, &stu->node);
    list_add_tail(&jill->node, &stu->node);
    list_add_tail(&fuchen->node, &stu->node);
    list_add_tail(&james->node, &stu->node);
    
    printf("原始链表：\n");
    show(stu);

    printf("将bill插入到fuchen后面：\n");
    list_add(&bill->node, &fuchen->node);
    show(stu);

    printf("删除Jack的学生信息：\n");
    list_del_init(&jack->node);
    show(stu);
    free(jack->name);
    free(jack);

    printf("销毁链表：\n");
    destroy_list(stu);
    printf("链表已销毁,保留头节点\n");

    if(stu)
        printf("头节点还未释放\n");

    free(stu);
    printf("头节点已释放\n");

    return 0;
}
#include <stdio.h>
struct node
{
    int data;
    char *ch;
    float f;
};


int main()
{
    struct node head = {3, "fuchen", 3.14};
    float *pf = &head.f;

    struct node *phead = (struct node*)((char *)pf - (unsigned long)(&((struct node *)0)->f));
    printf("%d\n", phead->data);
    printf("%s\n", phead->ch);
    printf("%f\n", phead->f);
}
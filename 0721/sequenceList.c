#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct{
    int capacity;
    int last;
    int *data;
}sequenceList;

sequenceList *init(int cap)
{
    sequenceList *s = malloc(sizeof(sequenceList));
    if (s != NULL )
    {
        s->capacity = cap;
        s->last     = -1;
        s->data = malloc(sizeof(int) * cap);
            if(s->data == NULL){
                free(s);
                return NULL;
    }
    return s;
}
}

int main(void)
{
    sequenceList *list= init_t(100);
    if(list == NULL)
        printf("初始化结构体失败");

    return 0;
}
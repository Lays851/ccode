#include "sqlist.h"

sqlist *init_sqlist(int cap)
{
    sqlist *sql = malloc(sizeof(sqlist));
    if (sql != NULL)
    {
        sql->capacity = cap;
        sql->last     = -1 ;
        sql->data = malloc(sizeof(int) * cap);
        if (sql->data == NULL){
            free(sql);
            return NULL;
        }
    }
    return sql;
}

bool add_data(sqlist *sql,int data)
{
    if (sql == NULL || sql->last + 1 == sql->capacity)
    {
        return false;
    }
    for(int i = 0; i <= sql->last; i++)
    {
        sql->data[sql->last+1-i] = sql->data[sql->last-i];
    }
    sql->data[0] = data;
    sql->last++;
    return true;
}

bool isEmpty(sqlist *sql)
{
    return sql == NULL || sql->last == -1;
}

bool del_data(sqlist *sql, int data)
{
    if (sql == NULL || isEmpty(sql))
    {
        return false;
    }

    for(int i = 0; i <= sql->last; i++)
    {
        if(sql->data[i] == data)
        {
            for(int j = i; j < sql->last; j++)
            {
                sql->data[j] = sql->data[j+1];
            }
            sql->last--;
            return true;
        }
    }
    return false;
}

void output(sqlist *sql)
{
    if(isEmpty(sql))
    {
        return;
    }

    for(int i = 0; i <= sql->last; i++)
    {
        printf("%d ",sql->data[i]);
    }
    printf("\n");
}

void swap(int *a,int *b)
{
    int tem = *a;
    *a = *b;
    *b = tem;    
}

void ppsort(sqlist *sql)
{
    int num = 0;
    if (isEmpty(sql))
    {
        return;
    }

    int n = sql->last;
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n-i; j++)
        {
            if(sql->data[j] > sql->data[j+1])
            {
                swap(&sql->data[j],&sql->data[j+1]);
                num++;
            }
        }
        if(num == 0)
            return;
    }
}

#ifndef _SQLIST_H
#define _SQLIST_H
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>


typedef struct sqlist
{
    int capacity;
    int last;
    int *data;
}sqlist;

sqlist * init_sqlist(int cap);
bool add_data(sqlist *sql,int data);
bool del_data(sqlist *sql,int data);
void output(sqlist *sql);
void reverse_output(sqlist *sql);
void sqlist_destroy(sqlist *sql);
void ppsort(sqlist *sql);
void swap(int *a,int *b);

#endif
#ifndef __HEAD_H
#define __HEAD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <strings.h>
#include <unistd.h>

typedef struct haxi
{
    char data[5];
    struct haxi *next;
} haxi;

static haxi *init()
{
    haxi *s = (haxi *)malloc(sizeof(haxi));
    if (s != NULL)
    {
        s->next = NULL;
    }
    return s;
}

char *zhifu()
{
    char a;
    char *b=malloc(5*sizeof(char));
    for(int i =0;i<4;i++)
    {
        a = rand()%(26)+97;
        b[i]=a;
    }
    b[4]='\0';
    return b;
}

static haxi *new_data(char *a)
{
    haxi *s = (haxi *)malloc(sizeof(haxi));
    if (s != NULL)
    {
        strcpy(s->data,a);
        s->next = NULL;
        free(a);
    }
    return s;
}

int zhifujisuan(haxi *new)
{
    int num = 0;
    for(int i=0;i<4;i++)
    {
        num += new->data[i];
    }
    return num;
}
static bool empty(haxi *head)
{
    if (head->next == NULL)
        return false;

    return true;
}

static bool add(haxi *head, haxi *newdata)
{
    if (empty(head) != true)
        head->next = newdata;
    else
    {
        for (; head->next != NULL; head = head->next)
            ;
        head->next = newdata;
    }
    return true;
}

static void show(haxi *head)
{
    if (empty(head) != true)
        return;
    head = head->next;
    for (; head != NULL; head = head->next)
    {
        printf("%s ", head->data);
    }
    return;
}

#endif
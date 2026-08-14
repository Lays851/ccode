#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <strings.h>

typedef struct node
{
    char str[10];
    struct node *next;
}node;

node *newnode(char str[])
{
    node *new = calloc(1, sizeof(struct node));
    if(new != NULL)
    {
        strcpy(new->str, str);
        new->next = NULL;        
    }
    return new;
}

typedef struct hash_table
{
    int hash_size;
    struct node ** table_entry;
}hashtable;

hashtable *init_hash(int hash_size)
{
    hashtable *init = calloc(1,sizeof(struct hash_table));
    if(init != NULL){
        init->hash_size = hash_size;
        init->table_entry = calloc(hash_size, sizeof(struct node *));
        if(init->table_entry == NULL)
        {
            free(init);
            return NULL;
        }
        for(int i=0; i<init->hash_size; i++)
        {
            init->table_entry[i] = calloc(1, sizeof(node));  
            init->table_entry[i]->next = NULL;
        }
    }
    return init;
}

void hash_add(hashtable *hash_table, char str[])
{
    int pos = (unsigned char)str[0]  % hash_table->hash_size;

    node *new = newnode(str);
    node *head = hash_table->table_entry[pos];
    if(head->next == NULL)
    {
        head->next = new;
    }
    else
    {
        while(head->next != NULL)
            head = head->next;
        head->next = new;
    }
    
}

void show(hashtable *ht)
{
    struct node *p;
    int i;
    for(i=0; i<ht->hash_size; i++)
    {
        p = ht->table_entry[i]->next;
        printf("table_entry[%d]: ", i);

        if(p != NULL)
        {
            struct node *q = p;
            while(q != NULL)
            {
                printf("%s\t", q->str);
                q = q->next;
            }
        }
        printf("\n");
    }
}

int find(hashtable *hash_table, char str[])
{
    int pos = str[0]  % hash_table->hash_size;
    node *tmp = hash_table->table_entry[pos];

    if(tmp->next == NULL)
        return -1;
    
    while(tmp->next != NULL)
    {
        if(!strcmp(tmp->next->str, str))
            return pos;
        tmp = tmp->next;
    }
    return -1;
}

int main(void)
{
    srand(time(NULL));
    int len ;
    hashtable *init = init_hash(20);
    char str[10], target[10];

    for(int i=0; i<20; i++)
    {
        memset(str, 0, sizeof(str)); 
        len = rand() % 4 + 1;
        int j = 0;
        for(j=0; j<len; j++)
        {   
            str[j] = 'a' + rand() % 26;
        }
        str[j] = '\0';
        hash_add(init, str);

        show(init);
        sleep(1);
    }


    while(1)
    {
        printf("请输入你要查找的字符串");
        fgets(target, 10, stdin);
        target[strcspn(target, "\n")] = '\0';
        int recode = find(init, target);
        if(recode == -1)
            printf("没有找到该字符串。");
        else
            printf("该字符串在table_entry[%d]",recode);
    }

    return 0;

}
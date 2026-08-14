#define DATATYPE char *
#include "head.h"
#define SIZE 20

char *rand_str(void)
{
    int i;
    int len = (rand() % 10) + 1;
    char *str = malloc(len + 1);
    if (!str)
        return NULL;
    for (i = 0; i < len; i++)
        str[i] = 'a' + (rand() % 26);
    str[len] = '\0';

    return str;
}

void show(hash_table *hashlist)
{
    for(int i=0; i<SIZE; i++)
    {
        printf("table_entry[%d]:", i);
        __typeof__(hashlist->table[i]) entry = hashlist->table[i];
        while (entry != NULL)
        {
            printf("%s ", entry->data);
            entry = entry->next;
        }
        printf("\n");
    }
}

unsigned short hash_func(char *data)
{
    unsigned short num = (data[0] + 1) % 20;
    return num;
}

int main(void)
{
    srand(time(NULL));
    //初始化管理结构体
    hash_table *hash_table = initHash(SIZE);
    if (hash_table)
        printf("初始化成功\n");
    else
        perror("初始化失败\n");

    // char *str = rand_str();
    // unsigned short num = hash_func(str);
    // printf("%s\n",str);
    // printf("%u\n",num);

    // show(hash_table);

    int count = 0;
    for (int i = 0; i < 20; i++)
    {
        char *str = rand_str();
        if (!str)
        {
            perror("生成字符串失败");
            continue;
        }

        hash_add(hash_table, str, hash_func);
        count++;

        system("clear");
        printf("inserted[%d]: %s\n", i + 1, str);
        show(hash_table);
        fflush(stdout);
        sleep(1);
    }

    char *str1 = NULL;
    printf("请输入查找的字符串：");
    scanf("%s", str1);
    int len = strlen(str1);
    str1[len] = '\0'; 

    int pos = find(hash_table, str1, hash_func);
    
    if(pos == -1)
        printf("没找到");
    else
        printf("在table_entry[%d]", pos);

    return 0;
}
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct player{
    char *name;
    int minute;
}player;

void swap(player *player1, player *player2)
{
    player tem = *player1;
    *player1 = *player2;
    *player2 = tem;
}

bool isbigger(player player1, player player2)
{
    return player1.minute > player2.minute;
}

void quicksort(struct player players[], int len)
{
    if(len <= 1)
        return;
    int i = 0;
    int j = len - 1;

    while(i < j)
    {
        while(!isbigger(players[i], players[j]) && i<j)
            j--;
        swap(&(players[i]),&(players[j]));

        while(!isbigger(players[i], players[j]) && i<j)
            i++;
        swap(&(players[i]),&(players[j]));
    }

    quicksort(players, i);
    quicksort(players + i + 1 , len - i - 1);
}

int main(void)
{
    player lisi = {"lisi", 2306};     
    player zhansan = {"zhansan", 1000};     
    player wangwu = {"wangwu", 3189};     
    player suantoujun = {"suantoujun", 4012};     
    player zhaoliu = {"zhaoliu", 2601};     
    struct player players[5] = {lisi, zhansan, wangwu,  suantoujun, zhaoliu};
    int len = 5;
    int lucky = rand() % 5;

    quicksort(players, len);
    printf("第%d名:%s获得奖励", lucky, players[lucky-1].name);

    return 0;
}
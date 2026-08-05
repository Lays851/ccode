#include <stdio.h>

struct date_t
{
    int year ;
    int month ;
    int day ;
};

void count(struct date_t date)
{
    int sum;
    sum = 30 * date.month + date.day;
    printf("%d年中的第%d天",date.year,sum);
}


int main(void)
{
    struct date_t date = {2026,7,18};
    count(date);

    struct date_t date1 = {
        .year = 2026,
        .month = 7,
        .day = 18};

    return 0;
}
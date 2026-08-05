#include "head.h"

int main(void)
{
    haxi *biao[20];
    for (int i = 0; i < 20; i++)
    {
        biao[i] = init();
    }

    for (int i = 0; i < 10; i++)
    {
        system("cls");
        char *a=zhifu();
        haxi *new = new_data(a);
        printf("================================\n");
        for (int j = 0; j < 20; j++)
        {
            if (j == zhifujisuan(new) % 20)
            {
                if (biao[j]->next == NULL)
                {
                    printf("biao[%d]:", j);
                    printf("\t<---%s\n", new->data);
                }
                else
                {
                    printf("biao[%d]:", j);
                    show(biao[j]);
                    printf("\t<---%s\n", new->data);
                }
                add(biao[j], new);
            }
            else
            {
                if (biao[j]->next == NULL)
                    printf("biao[%d]:\n", j);
                else
                {
                    printf("biao[%d]:", j);
                    show(biao[j]);
                    printf("\n");
                }
            }
        }
        printf("================================\n");
        sleep(1);
    }
    return 0;
}
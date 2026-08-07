#include <stdio.h>

int main()
{
    char p[] = "apple";
    int k = 0;
    for (int i = 0; p[i] != '\0'; i++)
    {   
        int j ;
        for (j = 0; p[j] != '\0'; j++)
        {
            if(p[i] == p[j])
            {
                break;
            }
        }
        if(j == i)
        {
            p[k++] = p[i];
        }
        
    }
    p[k] = '\0';
    printf("%s",p);
    return 0;
}
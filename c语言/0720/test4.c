#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[] = "asd.111,111";
    char *p = strtok(s,".,");

    while(p != NULL)
    {
        printf("%s\n",p);
        p = strtok(NULL,".,");
        
    }

    int a[] = {1,2,3,4,5};
    printf("%d\n",*(a+1));
    char *p1 = "123456";
    

    printf("%d",strlen(p1));

    return 0;

}
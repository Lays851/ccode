#include <stdio.h>
#include <stdlib.h>

int main(int argc, const char *argv[])
{
    // for(int i=0 ;i < argc ;i++)
    //     printf("参数[%d] :%s\n",i, argv[i]);

    // printf("char: %c\n", argv[2][2]);

  

    int *p = malloc(100);
    int *d = p;
    for(int i = 0 ;i < 25 ; i++)    
        *(d++) = i;
    printf("%d",p[1]);

    free(p);

    
    
    return 0;
}

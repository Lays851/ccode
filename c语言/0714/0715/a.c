#include <stdio.h>

void f3(char *p[3])
{
    for(int i=0 ; i<3 ; i++){
        printf("%s",p[i]);
    }
}

int main(void)
{
   char *s[3] = {"asd","zxc","kkk"};
   f3(s);
}
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// void strcon(char s1[], char s2[])
// {
//     int last_char = strlen(s1);
//     int len2 = strlen(s2);
//     for (int i = 0; i < len2; i++)
//         s1[last_char++] = s2[i];
//     s1[last_char] = '\0';
// }

void *str_connect(const char *s1,const char *s2)
{
    int len1 = 0, len2 = 0;
    for (int i = 0 ; s1[i] != '\0'; i++)
        ++len1;
    for (int i = 0 ; s2[i] != '\0'; i++)
        ++len2;

    char *result = malloc(len1 + len2 + 1);
    if(result == NULL)
        return NULL;
    char *d =result;
    
   
    for (int i = 0 ; s1[i] != '\0'; i++)
        *d++ = s1[i];
        
    for(int i = 0 ;s2[i] != '\0' ; i++)
        *d++ = s2[i];

    *d = '\0';  
    return result;  
}

int main(void)
{
    // char s1[] = "asdfg";
    // char s2[] = "hjkl";
    char *s3 = "abcde";
    char *s4 = "fghijk";


    // strcon(s1,s2);
    char *result = str_connect(s3,s4);

    // printf("%s\n",s1);
    printf("%s",result);

    return 0;
}
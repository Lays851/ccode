#include  <stdio.h>
#include  <string.h>

void cnec( char arr1[],  char arr2[] ,char arr3[])
{
    for(int i=0 ; i<(strlen(arr1) + strlen(arr2)) ; i++)
    {
        if(i < strlen(arr1))
            arr3[i] = arr1[i];
        else
            arr3[i] = arr2[i-strlen(arr1)];
    }
}

int main()
{
    char s1[] = "asdfg";
    char s2[] = "hjkl";
    char *s3 ;
    cnec(s1,s2,s3);
    printf("%s",s3);

    return 0;
}

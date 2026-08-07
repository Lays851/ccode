#include <stdio.h>
#include <stdlib.h>

char *str_concat(const char *s1, const char *s2)
{
    const char *p;
    size_t len1 = 0;
    size_t len2 = 0;

    for (p = s1; *p != '\0'; ++p) {
        ++len1;
    }
    for (p = s2; *p != '\0'; ++p) {
        ++len2;
    }

    char *result = malloc(len1 + len2 + 1);
    if (result == NULL) {
        return NULL;
    }

    char *d = result;
    for (p = s1; *p != '\0'; ++p) {
        *d++ = *p;
    }
    for (p = s2; *p != '\0'; ++p) {
        *d++ = *p;
    }
    *d = '\0';

    return result;
}

int main(void)
{
    const char *s1 = "Hello, ";
    const char *s2 = "world!";
    char *joined = str_concat(s1, s2);
    if (joined == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    printf("s1 = %s\n", s1);
    printf("s2 = %s\n", s2);
    printf("joined = %s\n", joined);

    free(joined);
    return 0;
}

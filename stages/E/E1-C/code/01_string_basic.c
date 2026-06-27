#include <stdio.h>
#include <string.h>

int my_strlen(const char *s);
char *my_strcpy(char *dest, const char *src);
int my_strcmp(const char *s1, const char *s2);

int main() {
    char s[10] = "1234A5";
    printf("len = %d\n", my_strlen(s));

    char s1[10];
    my_strcpy(s1, s);
    printf("s = %s\n", s);
    printf("s1 = %s\n", s1);

    char s2[10] = "1234B5";
    printf("cmp = %d\n", my_strcmp(s1, s2));

    return 0;
}

int my_strlen(const char *s) {
    int i = 0;
    while (s[i] != '\0') {
        i++;
    }
    return i;
}

char *my_strcpy(char *dest, const char *src) {
    int i = 0;
    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
    dest[i] = '\0';
    return dest;
}

int my_strcmp(const char *s1, const char *s2) {
    while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2) {
        s1++;
        s2++;
    }

    if (*s1 > *s2) {
        return 1;
    } else if (*s1 < *s2) {
        return -1;
    } else {
        return 0;
    }
}
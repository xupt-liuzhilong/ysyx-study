#include <stdio.h>

struct S {
    int a;
    double d;
    char str[10];
};

int main() {
    struct S s = {20, 3.14, "hello"};

    char buf[100];
    sprintf(buf, "%d %lf %s", s.a, s.d, s.str);

    printf("%s\n", buf);

    return 0;
}

#include <stdio.h>

int main()
{
    int age = 23;
    int *p = &age;

    printf("age = %d\n", age);
    printf("*(&age) = %d\n", *(&age));

    printf("*p = %d\n", *p);
    printf("&(*p) == p : %d\n", &(*p) == p);

    return 0;
}

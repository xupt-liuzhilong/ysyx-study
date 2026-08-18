#include <stdio.h>

void print_value(int *p) {
    printf("value = %d\n", *p);
}

int main() {
    int value = 42;
    int *ptr = &value;

    printf("before print_value\n");

    print_value(ptr);

    printf("after print_value\n");

    return 0;
}

#include <stdio.h>

int main() {
    int x = 2;

    if (x > 0) {
        printf("x > 0\n");
    } else if (x == 0) {
        printf("x == 0\\n");
    } else {
        printf("x < 0\n");
    }

    printf("\n--- for ---\n");

    for (int i = 0; i < 5; i++) {
        if (i == 2) {
            continue;
        }

        if (i == 4) {
            break;
        }

        printf("i = %d\n", i);
    }

    printf("\n--- switch ---\n");

    switch (x) {
        case 1:
            printf("one\n");
            break;
        case 2:
            printf("two\n");
            break;
        case 3:
            printf("three\n");
            break;
        default:
            printf("other\n");
            break;
    }


    int a = 5;

    if (a == 5) {
        printf("a equals 5\n");
    }

    if (a = 5) {
        printf("condition true, a = %d\n", a);
    }


    int n = 0;
    printf("\n--- while ---\n");

    while (n > 0) {
        printf("while: %d\n", n);
        n--;
    }

    printf("\n--- do while ---\n");
    do {
        printf("do while: %d\n", n);
        n--;
    } while (n > 0);


    return 0;
}

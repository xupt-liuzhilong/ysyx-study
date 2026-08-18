#include <stdio.h>

int main(int argc, char *argv[]) {
    int i = 0;

    printf("--- command line arguments ---\n");

    while (i < argc) {
        printf("argv[%d] = %s\n", i, argv[i]);
        i++;
    }


    printf("\n--- boolean expressions ---\n");

    int x = 3;

    printf("x > 0 = %d\n", x > 0);
    printf("x == 3 = %d\n", x == 3);
    printf("x != 3 = %d\n", x != 3);
    printf("x > 0 && x < 10 = %d\n", x > 0 && x < 10);
    printf("x < 0 || x == 3 = %d\n", x < 0 || x == 3);


    printf("\n--- argv with NULL ---\n");

    int j = 0;

    while (argv[j] != NULL) {
        printf("argv[%d] = %s\n", j, argv[j]);
        j++;
    }

    printf("argv[%d] = %p\n", j, (void *)argv[j]);


    printf("\n--- sentinel array ---\n");

    const char *names[] = {
        "alice",
        "bob",
        "charlie",
        NULL
    };

    int k = 0;

    while (names[k] != NULL) {
        printf("names[%d] = %s\n", k, names[k]);
        k++;
    }
    printf("names[%d] = %s\n", k, names[k]);

    return 0;
}

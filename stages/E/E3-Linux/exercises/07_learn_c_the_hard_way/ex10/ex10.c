#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    // go through each string in argv
    // why am I skipping argv[0]?
    for (i = 1; i < argc; i++) {
        printf("arg %d: %s\n", i, argv[i]);
    }

    // Let's make our own array of strings
    char *states[] = {
        "California",
        "Oregon",
        "Washington",
        "Texas"
    };

    int num_states = 4;

    for (i = 0; i < num_states; i++) {
        printf("state %d: %s\n", i, states[i]);
    }


    printf("\n--- argv detail ---\n");

    printf("argv[1] = %s\n", argv[1]);
    printf("argv[1][0] = %c\n", argv[1][0]);
    printf("argv[1][1] = %c\n", argv[1][1]);

    printf("argv[1] address = %p\n", (void *)argv[1]);
    printf("&argv[1][0] = %p\n", (void *)&argv[1][0]);
    return 0;
}

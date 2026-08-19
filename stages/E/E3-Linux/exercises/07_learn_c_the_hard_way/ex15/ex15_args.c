#include <stdio.h>

int main(int argc, char *argv[])
{
    char **cur_arg = argv;

    printf("argc =%d\n", argc);

    while (*cur_arg != NULL) {
        printf("%s\n", *cur_arg);
        cur_arg++;
    }

    return 0;
}

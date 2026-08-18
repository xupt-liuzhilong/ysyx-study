#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("argc = %d\n", argc);

    if (argc == 1) {
        printf("没有额外的命令行参数\n");
    } else if (argc <= 3) {
        printf("参数数量较少\n");
    }
    else {
        printf("参数数量较多\n");
    }

    for (int i = 0; i < argc; i++) {
        printf("argv[%d] = %s\n", i, argv[i]);
    }


    printf("\n--- truth value ---\n");

    if (0) {
        printf("0 is true\n");
    } else {
        printf("0 is false\n");
    }

    if (-1) {
        printf("-1 is true\n");
    }

    if (100) {
        printf("100 is true\n");
    }

    return 0;
}

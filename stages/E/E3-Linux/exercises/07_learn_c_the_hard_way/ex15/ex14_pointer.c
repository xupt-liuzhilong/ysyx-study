#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int i = 0;

    char *word = *(argv + 1);

    for (i = 0; *(word + i) != '\0'; i++){
        printf("'%c' == %d\n",
                *(word + i), *(word + i));
    }

    return 0;
}

#include <stdio.h>

void print_by_index(char **names, int *ages, int count)
{
    int i = 0;

    for (i = 0; i < count; i++) {
        printf("%s has %d years alive.\n",
                names[i], ages[i]);
    }
}

void print_by_pointer_offset(char **names, int *ages, int count)
{
    int i = 0;

    char **cur_name = names;
    int *cur_age = ages;

    for (i = 0; i < count; i++) {
        printf("%s is %d years old.\n",
                *(cur_name+i), *(cur_age+i));
    }
}

int main()
{
    // create two arrays we are about
    int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank",
        "Mary", "Joohn", "Lisa"
    };

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);

    // first way: indexing
    print_by_index(names, ages, count);


    printf("---\n");

    // second way: pointer + offset
    print_by_pointer_offset(names, ages, count);

    return 0;
}

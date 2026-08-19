#include <stdio.h>

int main()
{
    // create two arrays we are about
    int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Frank",
        "Mary", "John", "Lisa"
    };

    // safely get the size of ages
    int count = sizeof(ages) / sizeof(int);
    int i = 0;

    // array data accessed with pointer synax
    for (i = 0; i < count; i++) {
        printf("%s has %d years alive.\n",
                *(names+i), *(ages+i));
    }

    printf("---\n");


    // setup the pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;

    // second way using pointers
    for (i = 0; i < count; i++) {
        printf("%s is %d years old.\n",
                cur_name[i], cur_age[i]);
    }

    printf("---\n");

    // third way, pointers are just arrays
    for (i = 0; i < count; i++) {
        printf("%s is %d years old again.\n",
                cur_name[i], cur_age[i]);
    }

    printf("\n--- reverse traversal ---\n");

    for (i = count - 1; i >= 0; i--) {
        printf("%s is lived %d years so far.\n",
                cur_name[i], cur_age[i]);
    }

    printf("---\n");

    for (cur_age = ages + count - 1, cur_name = names + count - 1;
            (cur_age - ages) >= 0; cur_age--, cur_name--)
    {
        printf("%s is lived %d years so far.\n",
               * cur_name, *cur_age);
    }


    printf("---\n");
    cur_name = names + count;
    cur_age = ages + count;

    while (cur_age != ages) {
        cur_age--;
        cur_name--;

        printf("%s is lived %d years so far.\n",
               * cur_name, *cur_age);
    }

    return 0;
}

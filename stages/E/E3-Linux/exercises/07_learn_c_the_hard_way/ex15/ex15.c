#include <stdio.h>

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
    int i = 0;

    //first way using indexing
    for (i = 0; i < count; i++) {
        printf("%s has %d years alive.\n",
                names[i], ages[i]);
    }


    printf("\n--- pointer test ---\n");

    printf("ages[0] = %d\n", ages[0]);

    printf("*ages = %d\n", *ages);

    printf("*(ages+1) = %d\n", *(ages+1));

    printf("*(ages+2) = %d\n", *(ages+2));

    printf("---\n");


    // setup the pointers to the start of the arrays
    int *cur_age = ages;
    char **cur_name = names;

    // second way using pointers
    for (i = 0; i < count; i++) {
        printf("%s is %d years old.\n",
                *(cur_name+i), *(cur_age+i));
    }


    printf("\n--- pointer as array ---\n");

    printf("cur_age[0] = %d\n", cur_age[0]);
    printf("cur_age[1] = %d\n", cur_age[1]);

    printf("cur_name[0] = %s\n", cur_name[0]);
    printf("cur_name[1] = %s\n", cur_name[1]);


    printf("---\n");

    // third way, pointers are just arrays
    for (i = 0; i < count; i++) {
        printf("%s is %d years old again.\n",
                cur_name[i], cur_age[i]);
    }

    printf("---\n");


    printf("\n--- array vs pointer ---\n");

    printf("sizeof(ages) = %zu\n", sizeof(ages));
    printf("sizeof(cur_age) = %zu\n", sizeof(cur_age));

    printf("sizeof(names) = %zu\n", sizeof(names));
    printf("sizeof(cur_name) = %zu\n", sizeof(cur_name));

    printf("---\n");

    // fourth way with pointers in a stupid complex way
    for (cur_name = names, cur_age = ages;
            (cur_age - ages) < count;
            cur_name++, cur_age++)
    {
        printf("offest = %ld\n", cur_age - ages);

        printf("%s lived %d years so far.\n",
                *cur_name, *cur_age);
    }


    printf("\n--- pointer address ---\n");

    cur_age = ages;
    cur_name = names;

    for (i = 0; i < count; i++) {
        printf("age + %d = %p, cur_age = %p\n",
                i, (void *)(ages + i), (void *)cur_age);

        printf("names + %d = %p, cur_name =  %p\n",
                i, (void *)(names + i), (void *)cur_name);

        cur_age++;
        cur_name++;
    }

    return 0;
}

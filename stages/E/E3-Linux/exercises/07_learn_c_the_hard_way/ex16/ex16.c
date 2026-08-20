#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

struct Person {
    char *name;
    int age;
    int height;
    int weight;
};

struct Person *Person_create(char *name, int age, int height, int weight)
{
    struct Person *who = malloc(sizeof(struct Person));
    assert(who != NULL);

    who->name = strdup(name);
    who->age = age;
    who->height = height;
    who->weight = weight;

    return who;
}

void Person_destory(struct Person *who)
{
    assert(who != NULL);

    free(who->name);
    free(who);
}

void Person_print(struct Person *p)
{
    printf("Name: %s\n", p->name);
    printf("Age: %d\n", p->age);
    printf("Height: %d\n", p->height);
    printf("Weight: %d\n", p->weight);
}


int main()
{
    // make two people structures
    struct Person *joe = Person_create("Joe Alex", 32, 64, 140);
    struct Person *frank = Person_create("Frank Blank", 20, 72, 180);

    // print them out and where they are in memory
    printf("Joe is at memory locational %p:\n", (void *)joe);
    Person_print(joe);

    printf("---\n");

    printf("Frank is at memory locational %p:\n", (void *)frank);
    Person_print(frank);

    printf("---\n");

    // make everyone age 20 years and print them again
    joe->age += 20;
    joe->height -= 2;
    joe->weight += 40;
    Person_print(joe);

    printf("---\n");

    frank->age += 20;
    frank->weight += 20;
    Person_print(frank);

    // destory them both so we clean up
    Person_destory(joe);
    Person_destory(frank);

    return 0;
}

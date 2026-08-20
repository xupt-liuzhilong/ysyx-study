#include <stdio.h>

struct Person {
    char *name;
    int age;
    int height;
    int weight;

    char *eyes;
    char *hair;
};

void print_person(struct Person *p)
{
    printf("Name: %s\n", p->name);
    printf("Age: %d\n", p->age);
    printf("Height: %d\n", p->height);
    printf("Weight: %d\n", p->weight);
}


void Person_print(struct Person who)
{
    who.age = 100;
    printf("Name: %s\n", who.name);
    printf("Age: %d\n", who.age);
    printf("Height: %d\n", who.height);
    printf("Weight: %d\n", who.weight);
}

void change_age(struct Person *p)
{
    p->age = 20;
}

int main()
{
    struct Person joe = {"Joe", 10, 180, 70, "blue", "black"};
    struct Person frank = {"Frank", 30, 170, 80, "brown", "black"};


    change_age(&joe);
    print_person(&joe);
    printf("Eyes: %s\n", joe.eyes);
    printf("Hair: %s\n", joe.hair);


    printf("\n--- pointer test ---\n");

    struct Person *who = &joe;

    printf("Name: %s\n", who->name);
    printf("Age: %d\n", who->age);
    printf("Height: %d\n", who->height);
    printf("Weight: %d\n", who->weight);

    printf("\n---\n");

    Person_print(frank);

    printf("---\n");

    printf("frank.age = %d\n", frank.age);

    return 0;
}

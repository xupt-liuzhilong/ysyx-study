#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "game.h"

struct Map {
    Object proto;
    Room *start;
    Room *location;
};

typedef struct Map Map;

void *Map_move(void *self, Direction direction)
{
    assert(self != NULL);

    Map *map = self;
    assert(map->location != NULL);

    Room *next =
        map->location->_(move)(map->location, direction);

    if(next) {
        map->location = next;
    } else {
        // stay where we are
    }

    return next;
}

int Map_attack(void *self, int damage)
{
    assert(self != NULL);

    Map *map = self;
    assert(map->location != NULL);

    return map->location->_(attack)(
        map->location, damage);
}

int Map_init(void *self)
{
    assert(self != NULL);

    Map *map = self;

    Room *forest =
        NEW(Room, "A quiet forest");
    assert(forest != NULL);

    Room *cave =
        NEW(Room, "A dark cave");
    assert(cave != NULL);

    Room *tower =
        NEW(Room, "An abandoned tower");
    assert(tower != NULL);

    cave->bad_guy =
        NEW(Monster, "The ugly goblin");
    assert(cave->bad_guy != NULL);

    tower->bad_guy =
        NEW(Monster, "The ancient dragon");
    assert(tower->bad_guy != NULL);

    forest->north = cave;
    cave->south = forest;

    cave->east = tower;
    tower->west = cave;

    map->start = forest;
    map->location = forest;

    return 1;
}

Object MapProto = {
    .init = Map_init,
    .move = Map_move,
    .attack = Map_attack
};

int process_input(Map *game)
{
    assert(game != NULL);

    printf("\n> ");

    int ch = getchar();

    if(ch == EOF) {
        printf("Leaving the forest.\n");
        return 0;
    } else {
        getchar();
    }

    int damage = rand() % 4;

    switch(ch) {
        case 'n':
            game->_(move)(game, NORTH);
            break;

        case 's':
            game->_(move)(game, SOUTH);
            break;

        case 'e':
            game->_(move)(game, EAST);
            break;

        case 'w':
            game->_(move)(game, WEST);
            break;

        case 'a':
            game->_(attack)(game, damage);
            break;

        case 'l':
            printf("You can go:\n");

            if(game->location->north)
                printf("NORTH\n");

            if(game->location->south)
                printf("SOUTH\n");

            if(game->location->east)
                printf("EAST\n");

            if(game->location->west)
                printf("WEST\n");

            break;

        default:
            printf("What?: %d\n", ch);
    }

    return 1;
}

int main(void)
{
    srand(time(NULL));

    Map *game =
        NEW(Map, "The Forgotten Forest");

    assert(game != NULL);
    assert(game->location != NULL);

    printf("You enter ");
    game->location->_(describe)(game->location);

    while(process_input(game)) {
    }

    return 0;
}


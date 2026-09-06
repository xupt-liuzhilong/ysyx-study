#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>
#include "ex19.h"

void *Map_move(void *self, Direction direction)
{
    assert(self != NULL);
    assert(direction >= NORTH && direction <= WEST);

    Map *map = self;
    assert(map->location != NULL);
    assert(map->location->_(move) != NULL);

    Room *location = map->location;
    Room *next = NULL;

    next = location->_(move)(location, direction);

    if (next) {
        map->location = next;
    } else {
        // movement failed, keep current location
    }

    return next;
}

int Map_attack(void *self, int damage)
{
    assert(self != NULL);
    assert(damage >= 0);

    Map *map = self;

    assert(map->location != NULL);
    assert(map->location->_(attack) != NULL);

    Room *location = map->location;

    return location->_(attack)(location, damage);
}

int Map_init(void *self)
{
    assert(self != NULL);

    Map *map = self;

    // make some rooms for a small map
    Room *hall = NEW(Room, "The great Hall");
    assert(hall != NULL);

    Room *throne = NEW(Room, "The throne room");
    assert(throne != NULL);

    Room *arena = NEW(Room, "The arena, with the minotaur");
    assert(arena != NULL);

    Room *kitchen = NEW(Room, "Kitchen, you have the knife now");
    assert(kitchen != NULL);

    Room *cellar = NEW(Room, "The dark cellar");
    assert(cellar != NULL);

    // put the bad guy in the arena
    arena->bad_guy = NEW(Monster, "The evil minotaur");
    assert(arena->bad_guy != NULL);
    cellar->bad_guy = NEW(Monster, "The cave troll");
    assert(cellar->bad_guy != NULL);

    // setup the mao rooms
    hall->north = throne;

    throne->west = arena;
    throne->east = kitchen;
    throne->south = hall;

    arena->east = throne;

    kitchen->west = throne;
    kitchen->north = cellar;

    cellar->south = kitchen;

    // start the map and the character off in the hall
    map->start = hall;
    map->location = hall;

    assert(map->start != NULL);
    assert(map->location != NULL);

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
    assert(game->location != NULL);
    assert(game->_(move) != NULL);
    assert(game->_(attack) != NULL);

    printf("\n>");

    char ch = getchar();

    if (ch == EOF) {
        printf("Giving up? You suck.\n");
        return 0;
    } else {
        getchar(); // eat ENTER
    }

    int damage = rand() % 4;

    switch(ch) {
        case -1:
            printf("Giving up? You suck.\n");
            return 0;
            break;

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
            if (game->location->north)
                printf("NORTH\n");
            if (game->location->south)
                printf("SOUTH\n");
            if (game->location->east)
                printf("EAST\n");
            if (game->location->west)
                printf("WEST\n");
            break;

        default:
            printf("What?: %d\n", ch);
    }

    return 1;
}

int main(int argc, char *argv[])
{
    // simple way to setup the randomness
    srand(time(NULL));

    // make our map to work with
    Map *game = NEW(Map, "The Hall of the Minotaur.");
    assert(game != NULL);
    assert(game->location != NULL);
    assert(game->location->_(describe) != NULL);

    printf("You enter the ");
    game->location->_(describe)(game->location);

    while (process_input(game)) {}

    return 0;
}

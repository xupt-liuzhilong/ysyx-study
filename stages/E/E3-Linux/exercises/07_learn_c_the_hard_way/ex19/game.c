#include <stdio.h>
#include <assert.h>
#include "game.h"

int Monster_attack(void *self, int damage)
{
    assert(self != NULL);
    assert(damage >= 0);

    Monster *monster = self;
    assert(monster->_(description) != NULL);

    printf("You attack %s!\n", monster->_(description));

    monster->hit_points -= damage;

    if(monster->hit_points > 0) {
        printf("It is still alive.\n");
        return 0;
    } else {
        printf("It is dead!\n");
        return 1;
    }
}


int Monster_init(void *self)
{
    assert(self != NULL);

    Monster *monster = self;
    monster->hit_points = 10;

    assert(monster->hit_points > 0);

    return 1;
}

Object MonsterProto = {
    .init = Monster_init,
    .attack = Monster_attack
};

void *Room_move(void *self, Direction direction)
{
    assert(self != NULL);
    assert(direction >= NORTH && direction <= WEST);

    Room *room = self;
    Room *next = NULL;

    if(direction == NORTH && room ->north) {
        printf("You go north, into:\n");
        next = room->north;
    } else if (direction == SOUTH && room->south) {
        printf("You go south, into:\n");
        next = room->south;
    } else if (direction == EAST && room->east) {
        printf("You go east, into:\n");
        next = room->east;
    } else if (direction == WEST && room->west) {
        printf("you go west, into:\n");
        next = room->west;
    } else {
        printf("You can't go that direction.");
        next = NULL;
    }

    if (next) {
        assert(next->_(describe) != NULL);
        next->_(describe)(next);
    } else {
        // no room in that direction
    }

    return next;
}

int Room_attack(void *self, int damage)
{
    assert(self != NULL);
    assert(damage >= 0);

    Room *room = self;
    Monster *monster = room->bad_guy;

    if (monster) {
        assert(monster->_(attack) != NULL);

        monster->_(attack)(monster, damage);
        return 1;
    } else {
        printf("You flail in the air at nothing.Idiot.\n");
        return 0;
    }
}

Object RoomProto = {
    .move = Room_move,
    .attack = Room_attack
};


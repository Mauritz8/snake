#ifndef SNAKE_H
#define SNAKE_H

#include "coordinate.h"

typedef struct {
    Coord* units;
    int size;
} Snake;

typedef enum {UP, DOWN, LEFT, RIGHT} Direction;
bool legal_coordinate(Coord);
bool is_game_over(Snake*);

Snake create_snake(int size);
void print_snake(Snake);
void del_snake( Snake);
Coord new_unit(Snake*, Direction);
void move_snake(Snake*, Direction);
void grow_snake(Snake*, Direction);
bool is_occupied(Snake*, Coord pos);
Coord get_random_coord(Snake*);

#endif

#ifndef SNAKE_H
#define SNAKE_H

#include "coordinate.h"
#include <stddef.h>

typedef struct {
    Coord* units;
    size_t size;
} Snake;

typedef enum {UP, DOWN, LEFT, RIGHT} Direction;

Snake create_snake(size_t size);
void print_snake(const Snake* snake);
void del_snake(Snake* snake);
void move_snake(Snake* snake, Direction direction);
void grow_snake(Snake* snake, Direction direction);
Coord get_random_coord(const Snake* snake);
bool is_game_over(const Snake* snake);

#endif

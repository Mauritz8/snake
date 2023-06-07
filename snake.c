#include <stdlib.h>
#include <ncurses.h>
#include "snake.h"

bool can_move(enum direction dir) {
    return true;
}

struct Snake create_snake(int size) {
    struct Snake snake;
    struct Unit* units = malloc(sizeof(struct Unit) * size);
    for (int i = 0; i < size; i++) {
        struct Unit unit;
        unit.x = i;
        unit.y = 0;
        units[i] = unit;
    }
    snake.units = units;
    snake.size = size;
    return snake;
}

void print_snake(struct Snake snake) {
    for (int i = 0; i < snake.size; i++) {
        mvaddch(snake.units[i].y, snake.units[i].x, 'H');
    }
}

void del_snake(struct Snake snake) {
    for (int i = snake.size - 1; i >= 0; i--) {
        mvdelch(snake.units[i].y, snake.units[i].x);
    }
}

void move_up(struct Snake snake) {
    for (int i = 0; i < snake.size - 1; i++) {
        snake.units[i] = snake.units[i + 1];
    }
    
    struct Unit unit;
    unit.x = snake.units[snake.size - 2].x;
    unit.y = snake.units[snake.size - 2].y - 1;
    snake.units[snake.size - 1] = unit;
}

void move_down(struct Snake snake) {
    for (int i = 0; i < snake.size - 1; i++) {
        snake.units[i] = snake.units[i + 1];
    }
    
    struct Unit unit;
    unit.x = snake.units[snake.size - 2].x;
    unit.y = snake.units[snake.size - 2].y + 1;
    snake.units[snake.size - 1] = unit;
}

void move_left(struct Snake snake) {
    for (int i = 0; i < snake.size - 1; i++) {
        snake.units[i] = snake.units[i + 1];
    }
    
    struct Unit unit;
    unit.x = snake.units[snake.size - 2].x - 1;
    unit.y = snake.units[snake.size - 2].y;
    snake.units[snake.size - 1] = unit;
}

void move_right(struct Snake snake) {
    for (int i = 0; i < snake.size - 1; i++) {
        snake.units[i] = snake.units[i + 1];
    }
    
    struct Unit unit;
    unit.x = snake.units[snake.size - 2].x + 1;
    unit.y = snake.units[snake.size - 2].y;
    snake.units[snake.size - 1] = unit;
}

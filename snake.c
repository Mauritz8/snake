#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>
#include "snake.h"

bool can_move(struct snake snake, enum direction direction) {
    switch (direction) {
        case UP:
            if (snake.units[snake.size - 1].y - 1 < 0) {
                return false;
            }
        case DOWN:
            if (snake.units[snake.size - 1].y + 1 > LINES) {
                return false;
            }
        case LEFT:
            if (snake.units[snake.size - 1].x - 1 < 0) {
                return false;
            }
        case RIGHT:
            if (snake.units[snake.size - 1].x + 1 > COLS) {
                return false;
            }
    }
    return true;
}

struct snake create_snake(int size) {
    struct snake snake;
    struct unit* units = malloc(sizeof(struct unit) * size);
    for (int i = 0; i < size; i++) {
        struct unit unit;
        unit.x = COLS / 2;
        unit.y = i;
        units[i] = unit;
    }
    snake.units = units;
    snake.size = size;
    return snake;
}

void print_snake(struct snake snake) {
    for (int i = 0; i < snake.size; i++) {
        mvaddch(snake.units[i].y, snake.units[i].x, 'O');
    }
}

void del_snake(struct snake snake) {
    for (int i = 0; i < snake.size; i++) {
        mvaddch(snake.units[i].y, snake.units[i].x, ' ');
    }
}

void move_snake(struct snake* snake, enum direction direction) {
    for (int i = 0; i < snake->size - 1; i++) {
        snake->units[i] = snake->units[i + 1];
    }
    
    struct unit unit;
    switch (direction) {
        case UP:
            unit.x = snake->units[snake->size - 1].x;
            unit.y = snake->units[snake->size - 1].y - 1;
            break;
        case DOWN:
            unit.x = snake->units[snake->size - 1].x;
            unit.y = snake->units[snake->size - 1].y + 1;
            break;
        case LEFT:
            unit.x = snake->units[snake->size - 1].x - 1;
            unit.y = snake->units[snake->size - 1].y;
            break;
        case RIGHT:
            unit.x = snake->units[snake->size - 1].x + 1;
            unit.y = snake->units[snake->size - 1].y;
            break;
    }

    snake->units[snake->size - 1] = unit;
}

#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>

#include "snake.h"
#include "coordinate.h"
#include "board.h"

struct snake create_snake(int size) {
    struct snake snake;
    struct coord* units = malloc(sizeof(struct coord) * size);
    for (int i = 0; i < size; i++) {
        struct coord unit;
        unit.x = (getbegx(board) + getbegx(board) + getmaxx(board)) / 2;
        unit.y = getbegy(board) + 1 + i;
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

struct coord new_unit(struct snake* snake, enum direction direction) {
    struct coord unit;
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
    return unit;
}

bool legal_coordinate(struct coord coordinate) {
    if (coordinate.x <= getbegx(board)) {
        return false;
    } else if (coordinate.x >= getbegx(board) + getmaxx(board) - 1) {
        return false;
    } else if (coordinate.y <= getbegy(board)) {
        return false;
    } else if (coordinate.y >= getbegy(board) + getmaxy(board) - 1) {
        return false;
    }
    return true;
}

bool is_game_over(struct coord current_coordinate) {
    if (!legal_coordinate(current_coordinate)) {
        return true;
    }
    // should also check if snake has walked into itself
    return false;
}

void move_snake(struct snake* snake, enum direction direction) {
    for (int i = 0; i < snake->size - 1; i++) {
        snake->units[i] = snake->units[i + 1];
    }
    
    struct coord unit = new_unit(snake, direction);
    snake->units[snake->size - 1] = unit;
}

void grow_snake(struct snake* snake, enum direction direction) {
    snake->units = realloc(snake->units, sizeof(struct coord) * (snake->size + 1));
    for (int i = snake->size; i > 0; i--) {
        snake->units[i] = snake->units[i - 1];
    }

    struct coord unit = new_unit(snake, direction);
    snake->units[0] = unit;
    snake->size++;
}

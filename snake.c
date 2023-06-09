#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>

#include "snake.h"
#include "coordinate.h"
#include "board.h"
#include "utils.h"

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

bool is_legal_coordinate(struct coord coordinate) {
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

bool has_snake_walked_into_itself(struct snake* snake) {
    struct coord head = snake->units[snake->size - 1];
    for (int i = 0; i < snake->size - 1; i++) {
        struct coord unit = snake->units[i];
        if (unit.x == head.x && unit.y == head.y) {
            return true;
        } 
    }
    return false;
}

bool is_game_over(struct snake* snake) {
    struct coord head = snake->units[snake->size - 1];
    if (!is_legal_coordinate(head)) {
        return true;
    }
    if (has_snake_walked_into_itself(snake)) {
        return true;
    }

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

bool is_occupied(struct snake* snake, struct coord pos) {
    for (int i = 0; i < snake->size; i++) {
        if (snake->units[i].x == pos.x && snake->units[i].y == pos.y) {
            return true;
        }
    }
    return false;
}

struct coord get_random_coord(struct snake* snake) {
    struct coord coordinates;
    do {
        coordinates.x = get_random_num_in_range(getbegx(board) + 1, getbegx(board) + getmaxx(board) - 2);
        coordinates.y = get_random_num_in_range(getbegy(board) + 1, getbegy(board) + getmaxy(board) - 2);
    } while (is_occupied(snake, coordinates));

    return coordinates;
}

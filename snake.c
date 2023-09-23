#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <ncurses.h>

#include "snake.h"
#include "coordinate.h"
#include "board.h"
#include "utils.h"


static Coord new_unit(Snake* snake, Direction direction) {
    Coord unit;
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

static bool is_legal_coordinate(const Coord* coordinate) {
    if (coordinate->x <= getbegx(board)) {
        return false;
    } else if (coordinate->x >= getbegx(board) + getmaxx(board) - 1) {
        return false;
    } else if (coordinate->y <= getbegy(board)) {
        return false;
    } else if (coordinate->y >= getbegy(board) + getmaxy(board) - 1) {
        return false;
    }
    return true;
}

static bool has_snake_walked_into_itself(const Snake* snake) {
    Coord head = snake->units[snake->size - 1];
    for (int i = 0; i < snake->size - 1; i++) {
        Coord unit = snake->units[i];
        if (unit.x == head.x && unit.y == head.y) {
            return true;
        } 
    }
    return false;
}

static bool is_occupied(const Snake* snake, const Coord* pos) {
    for (int i = 0; i < snake->size; i++) {
        if (snake->units[i].x == pos->x && snake->units[i].y == pos->y) {
            return true;
        }
    }
    return false;
}

Snake create_snake(size_t size) {
    Snake snake;
    Coord* units = malloc(sizeof(Coord) * size);
    for (int i = 0; i < size; i++) {
        Coord unit;
        unit.x = (getbegx(board) + getbegx(board) + getmaxx(board)) / 2;
        unit.y = getbegy(board) + 1 + i;
        units[i] = unit;
    }
    snake.units = units;
    snake.size = size;
    return snake;
}

void print_snake(const Snake* snake) {
    for (int i = 0; i < snake->size; i++) {
        mvaddch(snake->units[i].y, snake->units[i].x, 'O');
    }
}

void del_snake(Snake* snake) {
    for (int i = 0; i < snake->size; i++) {
        mvaddch(snake->units[i].y, snake->units[i].x, ' ');
    }
}

void move_snake(Snake* snake, Direction direction) {
    for (int i = 0; i < snake->size - 1; i++) {
        snake->units[i] = snake->units[i + 1];
    }
    
    Coord unit = new_unit(snake, direction);
    snake->units[snake->size - 1] = unit;
}

void grow_snake(Snake* snake, Direction direction) {
    snake->units = realloc(snake->units, sizeof(Coord) * (snake->size + 1));
    for (int i = snake->size; i > 0; i--) {
        snake->units[i] = snake->units[i - 1];
    }

    Coord unit = new_unit(snake, direction);
    snake->units[0] = unit;
    snake->size++;
}

Coord get_random_coord(const Snake* snake) {
    Coord coordinate;
    do {
        coordinate.x = get_random_num_in_range(getbegx(board) + 1, getbegx(board) + getmaxx(board) - 2);
        coordinate.y = get_random_num_in_range(getbegy(board) + 1, getbegy(board) + getmaxy(board) - 2);
    } while (is_occupied(snake, &coordinate));

    return coordinate;
}

bool is_game_over(const Snake* snake) {
    const Coord head = snake->units[snake->size - 1];
    if (!is_legal_coordinate(&head)) {
        return true;
    }
    if (has_snake_walked_into_itself(snake)) {
        return true;
    }

    return false;
}

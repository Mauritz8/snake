#include <curses.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

struct Unit {
    int x;
    int y;
};

struct Snake {
    struct Unit* units;
    int size;
};

enum direction{up, down, left, right};

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

int main(void) {
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);


    int snake_size = 10;
    struct Snake snake = create_snake(snake_size);

    bool run = true;
    while (run) {
        print_snake(snake);
        refresh();

        int ch = getch();
        del_snake(snake);
        switch (ch) {
            case KEY_UP:
                move_up(snake);
                break;
            case KEY_DOWN:
                move_down(snake);
                break;
            case KEY_LEFT:
                move_left(snake);
                break;
            case KEY_RIGHT:
                move_right(snake);
                break;
            default:
                break;
        }
        napms(100);
    }

    endwin();

    return 0;
}

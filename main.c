#include <curses.h>
#include <ncurses.h>
#include "snake.h"


int main(void) {
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);


    int snake_size = 10;
    struct snake snake = create_snake(snake_size);

    enum direction direction = DOWN;
    bool run = true;
    while (run) {
        print_snake(snake);
        refresh();

        int input = getch();
        switch (input) {
            case KEY_UP:
                direction = UP;
                break;
            case KEY_DOWN:
                direction = DOWN;
                break;
            case KEY_LEFT:
                direction = LEFT;
                break;
            case KEY_RIGHT:
                direction = RIGHT;
                break;
        }

        del_snake(snake);
        if (can_move(snake, direction)) {
            move_snake(&snake, direction);
        } else {
            run = false;
        }
        napms(100);
    }

    endwin();
    printf("YOU LOST!!!\n");

    return 0;
}

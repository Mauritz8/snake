#include <curses.h>
#include <ncurses.h>
#include "snake.h"


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

#include <curses.h>
#include <ncurses.h>
#include <stdlib.h>

#include "coordinate.h"
#include "snake.h"
#include "food.h"
#include "board.h"


int main(void) {
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);

    const int BOARD_HEIGHT = 20;
    const int BOARD_WIDTH = 100;
    const int BOARD_STARTY = 10;
    const int BOARD_STARTX = 50;
    board = newwin(BOARD_HEIGHT, BOARD_WIDTH, BOARD_STARTY, BOARD_STARTX);
    box(board, 0, 0);
    refresh();
    wrefresh(board);


    int snake_size = 1;
    Snake snake = create_snake(snake_size);

    Coord food_coords = get_random_coord(&snake);
    place_food(&food_coords);

    int speed_ms = 100;

    Direction direction = DOWN;
    while (true) {
        print_snake(&snake);
        refresh();

        if (is_game_over(&snake)) {
            napms(1500);
            break;
        }

        bool eating = snake.units[snake.size - 1].x == food_coords.x &&
            snake.units[snake.size - 1].y == food_coords.y;
        if (eating) {
            grow_snake(&snake, direction);
            food_coords = get_random_coord(&snake);
            place_food(&food_coords);
            speed_ms -= 1;
        }


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
        del_snake(&snake);
        move_snake(&snake, direction);

        if (direction == UP || direction == DOWN) {
            napms(speed_ms * 2);
        } else {
            napms(speed_ms);
        }
    }

    endwin();
    printf("YOU LOST\n");
    printf("Score: %zu\n", snake.size);

    free(snake.units);
    return 0;
}

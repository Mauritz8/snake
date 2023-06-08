#include <curses.h>
#include <ncurses.h>

#include "coordinate.h"
#include "snake.h"
#include "food.h"


int main(void) {
    initscr();
    cbreak();
    noecho();
    curs_set(FALSE);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);


    int snake_size = 3;
    struct snake snake = create_snake(snake_size);

    struct coord food_coords = get_random_coord();
    place_food(food_coords);

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
            bool eating = snake.units[snake.size - 1].x == food_coords.x &&
                snake.units[snake.size - 1].y == food_coords.y; 
            if (eating) {
                grow_snake(&snake, direction);
                food_coords = get_random_coord();
                place_food(food_coords);
            }
        } else {
            run = false;
        }
        napms(50);
    }

    endwin();
    printf("YOU LOST\n");
    printf("Score: %d\n", snake.size);

    return 0;
}

#include <curses.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#include "coordinate.h"
#include "board.h"

int get_random_num_in_range(int lower_bound, int upper_bound) {
    srand(time(NULL));
    return rand() % ((upper_bound + 1) - lower_bound) + lower_bound;
}

struct coord get_random_coord() {
    struct coord coordinates;
    coordinates.x = get_random_num_in_range(getbegx(board) + 1, getbegx(board) + getmaxx(board) - 2);
    coordinates.y = get_random_num_in_range(getbegy(board) + 1, getbegy(board) + getmaxy(board) - 2);
    return coordinates;
}

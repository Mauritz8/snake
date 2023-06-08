#include <curses.h>
#include <ncurses.h>
#include <time.h>
#include <stdlib.h>

#include "coordinate.h"

int get_random_num_in_range(int lower_bound, int upper_bound) {
    srand(time(NULL));
    return rand() % ((upper_bound + 1) - lower_bound) + lower_bound;
}

struct coord get_random_coord() {
    struct coord coordinates;
    coordinates.x = get_random_num_in_range(0, COLS);
    coordinates.y = get_random_num_in_range(0, LINES);
    return coordinates;
}

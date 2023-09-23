#include <curses.h>

#include "coordinate.h"
#include "food.h"

void place_food(const Coord* food_coords) {
    mvaddch(food_coords->y, food_coords->x, '*');
}

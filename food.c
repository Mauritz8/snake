#include <curses.h>

#include "coordinate.h"
#include "food.h"

void place_food(Coord food_coords) {
    mvaddch(food_coords.y, food_coords.x, '*');
}

#include <curses.h>

#include "coordinate.h"
#include "food.h"

void place_food(struct coord food_coords) {
    mvaddch(food_coords.y, food_coords.x, 'F');
}

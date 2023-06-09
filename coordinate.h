#ifndef COORDINATE_H
#define COORDINATE_H

#include <curses.h>

struct coord {
    int x;
    int y;
};
struct coord get_random_coord();

#endif

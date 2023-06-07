#ifndef SNAKE_H
#define SNAKE_H

struct unit {
    int x;
    int y;
};

struct snake {
    struct unit* units;
    int size;
};

enum direction{UP, DOWN, LEFT, RIGHT};
bool can_move(struct snake, enum direction);

struct snake create_snake(int size);
void print_snake(struct snake);
void del_snake(struct snake);
void move_snake(struct snake, enum direction);

#endif

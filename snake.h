#ifndef SNAKE_H
#define SNAKE_H

struct snake {
    struct coord* units;
    int size;
};

enum direction{UP, DOWN, LEFT, RIGHT};
bool can_move(struct snake, enum direction);

struct snake create_snake(int size);
void print_snake(struct snake);
void del_snake(struct snake);
struct coord new_unit(struct snake*, enum direction);
void move_snake(struct snake*, enum direction);
void grow_snake(struct snake*, enum direction);

#endif

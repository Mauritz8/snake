#ifndef SNAKE_H
#define SNAKE_H

struct Unit {
    int x;
    int y;
};

struct Snake {
    struct Unit* units;
    int size;
};

enum direction{up, down, left, right};
bool can_move(enum direction dir);

struct Snake create_snake(int size);
void print_snake(struct Snake snake);
void del_snake(struct Snake snake);
void move_up(struct Snake snake);
void move_down(struct Snake snake);
void move_left(struct Snake snake);
void move_right(struct Snake snake);

#endif

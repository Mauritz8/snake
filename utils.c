#include <time.h>
#include <stdlib.h>

int get_random_num_in_range(int lower_bound, int upper_bound) {
    srand(time(NULL));
    return rand() % ((upper_bound + 1) - lower_bound) + lower_bound;
}

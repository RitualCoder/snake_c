#ifndef SNAKE_H
#define SNAKE_H

#include <stdbool.h>

#define MAX_SNAKE 256

typedef struct
{
    int x, y;
} Point;
typedef enum
{
    UP = 0,
    RIGHT = 1,
    DOWN = 2,
    LEFT = 3
} Direction;

// renvoie true si la tête (snake[0]) touche un autre segment
bool check_self_collision(const Point snake[], int len);

#endif // SNAKE_H

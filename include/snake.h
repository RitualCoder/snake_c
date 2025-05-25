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
    UP,
    RIGHT,
    DOWN,
    LEFT
} Direction;

// Vérifie auto-collision (la tête vs le reste du corps)
bool check_self_collision(const Point snake[], int len);

#endif // SNAKE_H

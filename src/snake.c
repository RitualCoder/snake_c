#include "snake.h"

bool check_self_collision(const Point snake[], int len)
{
    for (int i = 1; i < len; i++)
    {
        if (snake[i].x == snake[0].x &&
            snake[i].y == snake[0].y)
            return true;
    }
    return false;
}

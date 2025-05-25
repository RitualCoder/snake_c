#include "apple.h"
#include "game.h"
#include <stdlib.h>

Point apple;

void spawn_apple(const Point snake[], int len)
{
    bool conflict;
    do
    {
        conflict = false;
        apple.x = rand() % GRID_W;
        apple.y = rand() % GRID_H;
        for (int i = 0; i < len; i++)
        {
            if (snake[i].x == apple.x && snake[i].y == apple.y)
            {
                conflict = true;
                break;
            }
        }
    } while (conflict);
}

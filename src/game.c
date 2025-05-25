#include "game.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <SDL2/SDL_ttf.h>

GameState state = STATE_MENU;
Point snake[MAX_SNAKE];
Point prev_snake[MAX_SNAKE];
int snake_len;
Direction dir;
Point apple;

void init_game(void)
{
    snake_len = 5;
    dir = RIGHT;
    state = STATE_PLAYING;
    int midY = GRID_H / 2;
    for (int i = 0; i < snake_len; i++)
    {
        snake[i].x = snake_len - 1 - i;
        snake[i].y = midY;
        prev_snake[i] = snake[i];
    }
    srand((unsigned)time(NULL));
    spawn_apple(snake, snake_len);
}

void update_game(void)
{
    if (state != STATE_PLAYING)
        return;

    memcpy(prev_snake, snake, snake_len * sizeof(Point));

    Point head = snake[0];
    switch (dir)
    {
    case UP:
        head.y--;
        break;
    case DOWN:
        head.y++;
        break;
    case LEFT:
        head.x--;
        break;
    case RIGHT:
        head.x++;
        break;
    }

    // collision mur → game over
    if (head.x < 0 || head.x >= GRID_W ||
        head.y < 0 || head.y >= GRID_H)
    {
        state = STATE_GAMEOVER;
        return;
    }

    snake[0] = head;
    if (check_self_collision(snake, snake_len))
    {
        state = STATE_GAMEOVER;
        return;
    }

    bool grow = (head.x == apple.x && head.y == apple.y);
    Point old_tail = snake[snake_len - 1];
    if (grow && snake_len < MAX_SNAKE)
    {
        snake_len++;
        spawn_apple(snake, snake_len);
    }

    for (int i = snake_len - 1; i > 0; i--)
    {
        snake[i] = snake[i - 1];
    }
    snake[0] = head;

    if (grow)
    {
        prev_snake[snake_len - 1] = old_tail;
    }
}

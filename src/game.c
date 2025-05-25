#include "game.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

GameState state = STATE_MENU;
Point snake[MAX_SNAKE];
Point prev_snake[MAX_SNAKE]; // non utilisé mais gardé
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
    }
    srand((unsigned)time(NULL));
    spawn_apple(snake, snake_len);
}

void update_game(void)
{
    if (state != STATE_PLAYING)
        return;

    // recopie prev_snake si besoin (pas utilisé render ici)
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

    // mur → game over
    if (head.x < 0 || head.x >= GRID_W ||
        head.y < 0 || head.y >= GRID_H)
    {
        state = STATE_GAMEOVER;
        return;
    }

    // self collision
    for (int i = 1; i < snake_len; i++)
        if (snake[i].x == head.x && snake[i].y == head.y)
        {
            state = STATE_GAMEOVER;
            return;
        }

    // pousse le corps
    for (int i = snake_len - 1; i > 0; i--)
        snake[i] = snake[i - 1];
    snake[0] = head;

    // croissance ?
    if (head.x == apple.x && head.y == apple.y && snake_len < MAX_SNAKE)
    {
        snake_len++;
        spawn_apple(snake, snake_len);
    }
}

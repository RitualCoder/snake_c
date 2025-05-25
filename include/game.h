#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "apple.h"

#define GRID_W 32
#define GRID_H 24
#define TILE_SIZE 20
#define MAX_SNAKE 256

typedef enum
{
    STATE_MENU,
    STATE_PLAYING,
    STATE_GAMEOVER
} GameState;

extern GameState state;

extern Point snake[MAX_SNAKE];
extern Point prev_snake[MAX_SNAKE];
extern int snake_len;
extern Direction dir;

extern Point apple;

void init_game(void);
void update_game(void);

#endif // GAME_H

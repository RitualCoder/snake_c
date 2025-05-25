#ifndef GAME_H
#define GAME_H

#include "snake.h"
#include "apple.h"

#define GRID_W 15
#define GRID_H 15
#define TILE_SIZE 30

typedef enum
{
    STATE_MENU,
    STATE_PLAYING,
    STATE_GAMEOVER
} GameState;

extern GameState state;
extern Point snake[MAX_SNAKE];
extern Point prev_snake[MAX_SNAKE]; // pas utilisé ici, mais gardé pour cohérence
extern int snake_len;
extern Direction dir;

void init_game(void);
void update_game(void);

#endif // GAME_H

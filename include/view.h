// include/view.h
#ifndef VIEW_H
#define VIEW_H
#include <SDL2/SDL.h>

// rectangles exposés pour input.c
extern const SDL_Rect btnPlay;
extern const SDL_Rect btnRestart;

void render_menu(void);
void render_gameover(void);
#endif

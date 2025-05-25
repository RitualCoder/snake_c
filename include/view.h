#ifndef VIEW_H
#define VIEW_H

#include <SDL2/SDL.h>

// boutons exposés pour input.c
extern const SDL_Rect btnPlay;
extern const SDL_Rect btnRestart;

// rend le menu
void render_menu(void);
// rend l’écran Game Over
void render_gameover(void);

#endif // VIEW_H

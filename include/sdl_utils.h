// include/sdl_utils.h
#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

extern SDL_Window   *window;
extern SDL_Renderer *renderer;
extern TTF_Font     *font;

bool init_SDL(void);
void shutdown_SDL(void);

#endif // SDL_UTILS_H

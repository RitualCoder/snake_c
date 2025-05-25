#ifndef SDL_UTILS_H
#define SDL_UTILS_H

#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_image.h>

// window, renderer et font définis en sdl_utils.c
extern SDL_Window   *window;
extern SDL_Renderer *renderer;
extern TTF_Font     *font;

// textures pour le serpent et la pomme
extern SDL_Texture *textureApple;
extern SDL_Texture *textureHead[4];
extern SDL_Texture *textureBodyHorizontal;
extern SDL_Texture *textureBodyVertical;
extern SDL_Texture *textureBodyCorner[4];
extern SDL_Texture *textureTail[4];

// initialise SDL, TTF, IMG, window, renderer, font et textures
bool init_SDL(void);
// détruit tout proprement
void shutdown_SDL(void);

#endif // SDL_UTILS_H

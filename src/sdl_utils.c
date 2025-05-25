#include "sdl_utils.h"
#include "game.h"
#include <SDL2/SDL_ttf.h>
#include <stdio.h>

// définitions des globals
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;

SDL_Texture *textureApple = NULL;
SDL_Texture *textureHead[4];
SDL_Texture *textureBodyHorizontal;
SDL_Texture *textureBodyVertical;
SDL_Texture *textureBodyCorner[4];
SDL_Texture *textureTail[4];

static SDL_Texture *load(const char *path)
{
    SDL_Texture *t = IMG_LoadTexture(renderer, path);
    if (!t)
        SDL_Log("IMG_LoadTexture %s: %s", path, IMG_GetError());
    return t;
}

bool init_SDL(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0 ||
        TTF_Init() != 0 ||
        IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG)
    {
        SDL_Log("Init SDL/TTF/IMG error: %s / %s", SDL_GetError(), TTF_GetError());
        return false;
    }

    window = SDL_CreateWindow("Snake SDL2",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              GRID_W * TILE_SIZE, GRID_H * TILE_SIZE,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI);
    if (!window)
        return false;

    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
        return false;

    SDL_RenderSetLogicalSize(
        renderer,
        GRID_W * TILE_SIZE,
        GRID_H * TILE_SIZE);

    // charge la font
    font = TTF_OpenFont("assets/fonts/Verdana.ttf", 24);
    if (!font)
        return false;

    // charge les textures
    textureApple = load("assets/images/apple.png");
    for (int d = 0; d < 4; d++)
        textureHead[d] = load((const char *[]){
            "assets/images/head_up.png",
            "assets/images/head_right.png",
            "assets/images/head_down.png",
            "assets/images/head_left.png"}[d]);
    textureBodyHorizontal = load("assets/images/body_horizontal.png");
    textureBodyVertical = load("assets/images/body_vertical.png");
    textureBodyCorner[0] = load("assets/images/body_bottomleft.png");
    textureBodyCorner[1] = load("assets/images/body_topleft.png");
    textureBodyCorner[2] = load("assets/images/body_topright.png");
    textureBodyCorner[3] = load("assets/images/body_bottomright.png");
    for (int d = 0; d < 4; d++)
        textureTail[d] = load((const char *[]){
            "assets/images/tail_up.png",
            "assets/images/tail_right.png",
            "assets/images/tail_down.png",
            "assets/images/tail_left.png"}[d]);

    return true;
}

void shutdown_SDL(void)
{
    // détruit textures
    SDL_DestroyTexture(textureApple);
    for (int i = 0; i < 4; i++)
        SDL_DestroyTexture(textureHead[i]);
    SDL_DestroyTexture(textureBodyHorizontal);
    SDL_DestroyTexture(textureBodyVertical);
    for (int i = 0; i < 4; i++)
        SDL_DestroyTexture(textureBodyCorner[i]);
    for (int i = 0; i < 4; i++)
        SDL_DestroyTexture(textureTail[i]);

    if (font)
        TTF_CloseFont(font);
    if (renderer)
        SDL_DestroyRenderer(renderer);
    if (window)
        SDL_DestroyWindow(window);
    IMG_Quit();
    TTF_Quit();
    SDL_Quit();
}

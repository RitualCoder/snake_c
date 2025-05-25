// src/sdl_utils.c
#include "sdl_utils.h"
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

// Définitions des globals
SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
TTF_Font *font = NULL;

// Initialise SDL, TTF, crée window/renderer et charge la font
bool init_SDL(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        SDL_Log("SDL_Init error: %s", SDL_GetError());
        return false;
    }
    if (TTF_Init() != 0)
    {
        SDL_Log("TTF_Init error: %s", TTF_GetError());
        SDL_Quit();
        return false;
    }

    window = SDL_CreateWindow("Snake SDL2",
                              SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                              GRID_W * TILE_SIZE, GRID_H * TILE_SIZE,
                              SDL_WINDOW_SHOWN | SDL_WINDOW_ALLOW_HIGHDPI // ← active High-DPI
    );

    if (!window)
    {
        SDL_Log("SDL_CreateWindow error: %s", SDL_GetError());
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1,
                                  SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer)
    {
        SDL_Log("SDL_CreateRenderer error: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    SDL_RenderSetLogicalSize(
        renderer,
        GRID_W * TILE_SIZE,
        GRID_H * TILE_SIZE);

    int output_w, output_h;
    SDL_GetRendererOutputSize(renderer, &output_w, &output_h);
    // output_w/h est la taille en **pixels** physiques
    // GRID_W*TILE_SIZE et GRID_H*TILE_SIZE sont en tailles logiques

    float dpi_scale_x = output_w / (float)(GRID_W * TILE_SIZE);
    float dpi_scale_y = output_h / (float)(GRID_H * TILE_SIZE);

    // Charge la font
    font = TTF_OpenFont("assets/fonts/Verdana.ttf", 24);
    if (!font)
    {
        SDL_Log("TTF_OpenFont error: %s", TTF_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    return true;
}

// Détruit la font, le renderer, la window et quitte SDL/TTF
void shutdown_SDL(void)
{
    if (font)
    {
        TTF_CloseFont(font);
        font = NULL;
    }
    TTF_Quit();

    if (renderer)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }
    SDL_Quit();
}

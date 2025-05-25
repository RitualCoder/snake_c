#include "render.h"
#include "game.h"
#include <SDL2/SDL.h>

extern SDL_Renderer *renderer;

void render_game(float t)
{
    // efface
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // damier
    for (int y = 0; y < GRID_H; y++)
        for (int x = 0; x < GRID_W; x++)
        {
            SDL_Rect cell = {x * TILE_SIZE, y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
            if ((x + y) % 2 == 0)
                SDL_SetRenderDrawColor(renderer, 170, 215, 81, 255);
            else
                SDL_SetRenderDrawColor(renderer, 162, 209, 73, 255);
            SDL_RenderFillRect(renderer, &cell);
        }

    // pomme
    SDL_Rect a = {apple.x * TILE_SIZE, apple.y * TILE_SIZE, TILE_SIZE, TILE_SIZE};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderFillRect(renderer, &a);

    // serpent interpolé
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    for (int i = 0; i < snake_len; i++)
    {
        float fx = prev_snake[i].x * (1 - t) + snake[i].x * t;
        float fy = prev_snake[i].y * (1 - t) + snake[i].y * t;
        SDL_Rect s = {(int)(fx * TILE_SIZE), (int)(fy * TILE_SIZE), TILE_SIZE, TILE_SIZE};
        SDL_RenderFillRect(renderer, &s);
    }

    SDL_RenderPresent(renderer);
}

#include "view.h"
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

extern SDL_Renderer *renderer;
extern TTF_Font *font;

const SDL_Rect btnPlay = {
    .x = (GRID_W * TILE_SIZE) / 2 - 100,
    .y = (GRID_H * TILE_SIZE) / 2 - 25,
    .w = 200,
    .h = 50};
const SDL_Rect btnRestart = {
    .x = (GRID_W * TILE_SIZE) / 2 - 100,
    .y = (GRID_H * TILE_SIZE) / 2 + 40,
    .w = 200,
    .h = 50};

void render_menu(void)
{
    SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 70, 70, 100, 255);
    SDL_RenderFillRect(renderer, &btnPlay);
    SDL_SetRenderDrawColor(renderer, 200, 200, 220, 255);
    SDL_RenderDrawRect(renderer, &btnPlay);

    SDL_Surface *s = TTF_RenderText_Blended(font, "Play", (SDL_Color){255, 255, 255, 255});
    SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, s);
    SDL_Rect d = {btnPlay.x + (btnPlay.w - s->w) / 2,
                  btnPlay.y + (btnPlay.h - s->h) / 2,
                  s->w, s->h};
    SDL_FreeSurface(s);
    SDL_RenderCopy(renderer, t, NULL, &d);
    SDL_DestroyTexture(t);

    SDL_RenderPresent(renderer);
}

void render_gameover(void)
{
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
    SDL_RenderClear(renderer);

    SDL_Surface *s = TTF_RenderText_Blended(font, "You lose!", (SDL_Color){255, 255, 255, 255});
    SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, s);
    SDL_Rect d = {(GRID_W * TILE_SIZE - s->w) / 2, (GRID_H * TILE_SIZE) / 2 - s->h - 10,
                  s->w, s->h};
    SDL_FreeSurface(s);
    SDL_RenderCopy(renderer, t, NULL, &d);
    SDL_DestroyTexture(t);

    SDL_SetRenderDrawColor(renderer, 70, 70, 100, 255);
    SDL_RenderFillRect(renderer, &btnRestart);
    SDL_SetRenderDrawColor(renderer, 200, 200, 220, 255);
    SDL_RenderDrawRect(renderer, &btnRestart);

    s = TTF_RenderText_Blended(font, "Restart", (SDL_Color){255, 255, 255, 255});
    t = SDL_CreateTextureFromSurface(renderer, s);
    d = (SDL_Rect){btnRestart.x + (btnRestart.w - s->w) / 2,
                   btnRestart.y + (btnRestart.h - s->h) / 2,
                   s->w, s->h};
    SDL_FreeSurface(s);
    SDL_RenderCopy(renderer, t, NULL, &d);
    SDL_DestroyTexture(t);

    SDL_RenderPresent(renderer);
}

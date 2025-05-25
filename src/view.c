// src/view.c
#include "view.h"
#include "game.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

extern TTF_Font *font;
extern SDL_Renderer *renderer;

static const SDL_Color white = {255, 255, 255, 255};
static const SDL_Color btnBg = {70, 70, 100, 255};
static const SDL_Color btnEd = {200, 200, 220, 255};

// <-- Retiré static ici !
const SDL_Rect btnPlay = {
    .x = (GRID_W * TILE_SIZE) / 2 - 100,
    .y = (GRID_H * TILE_SIZE) / 2 - 25,
    .w = 200,
    .h = 50};

// <-- Et ici !
const SDL_Rect btnRestart = {
    .x = (GRID_W * TILE_SIZE) / 2 - 100,
    .y = (GRID_H * TILE_SIZE) / 2 + 40,
    .w = 200,
    .h = 50};

void render_menu(void)
{
    SDL_SetRenderDrawColor(renderer, 20, 20, 30, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, btnBg.r, btnBg.g, btnBg.b, btnBg.a);
    SDL_RenderFillRect(renderer, &btnPlay);
    SDL_SetRenderDrawColor(renderer, btnEd.r, btnEd.g, btnEd.b, btnEd.a);
    SDL_RenderDrawRect(renderer, &btnPlay);

    SDL_Surface *s = TTF_RenderText_Blended(font, "Play", white);
    SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, s);
    SDL_Rect dst = {
        btnPlay.x + (btnPlay.w - s->w) / 2,
        btnPlay.y + (btnPlay.h - s->h) / 2,
        s->w, s->h};
    SDL_FreeSurface(s);
    SDL_RenderCopy(renderer, t, NULL, &dst);
    SDL_DestroyTexture(t);

    SDL_RenderPresent(renderer);
}

void render_gameover(void)
{
    SDL_SetRenderDrawColor(renderer, 10, 10, 10, 255);
    SDL_RenderClear(renderer);

    SDL_Surface *s = TTF_RenderText_Blended(font, "You lose!", white);
    SDL_Texture *t = SDL_CreateTextureFromSurface(renderer, s);
    SDL_Rect dst = {
        (GRID_W * TILE_SIZE - s->w) / 2,
        (GRID_H * TILE_SIZE) / 2 - s->h - 10,
        s->w, s->h};
    SDL_FreeSurface(s);
    SDL_RenderCopy(renderer, t, NULL, &dst);
    SDL_DestroyTexture(t);

    SDL_SetRenderDrawColor(renderer, btnBg.r, btnBg.g, btnBg.b, btnBg.a);
    SDL_RenderFillRect(renderer, &btnRestart);
    SDL_SetRenderDrawColor(renderer, btnEd.r, btnEd.g, btnEd.b, btnEd.a);
    SDL_RenderDrawRect(renderer, &btnRestart);

    s = TTF_RenderText_Blended(font, "Restart", white);
    t = SDL_CreateTextureFromSurface(renderer, s);
    dst = (SDL_Rect){
        btnRestart.x + (btnRestart.w - s->w) / 2,
        btnRestart.y + (btnRestart.h - s->h) / 2,
        s->w, s->h};
    SDL_FreeSurface(s);
    SDL_RenderCopy(renderer, t, NULL, &dst);
    SDL_DestroyTexture(t);

    SDL_RenderPresent(renderer);
}

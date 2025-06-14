#include "input.h"
#include "game.h"
#include "view.h"
#include <SDL2/SDL.h>

void handle_input(bool *running)
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            *running = false;
        }
        else if (e.type == SDL_KEYDOWN)
        {
            switch (e.key.keysym.sym)
            {
            case SDLK_UP:
                if (state == STATE_PLAYING && dir != DOWN)
                    dir = UP;
                break;
            case SDLK_DOWN:
                if (state == STATE_PLAYING && dir != UP)
                    dir = DOWN;
                break;
            case SDLK_LEFT:
                if (state == STATE_PLAYING && dir != RIGHT)
                    dir = LEFT;
                break;
            case SDLK_RIGHT:
                if (state == STATE_PLAYING && dir != LEFT)
                    dir = RIGHT;
                break;
            case SDLK_RETURN:
            case SDLK_r:
                if (state == STATE_MENU || state == STATE_GAMEOVER)
                    init_game();
                break;
            case SDLK_ESCAPE:
                *running = false;
                break;
            }
        }
        else if (e.type == SDL_MOUSEBUTTONDOWN && e.button.button == SDL_BUTTON_LEFT)
        {
            int mx = e.button.x, my = e.button.y;
            if (state == STATE_MENU &&
                mx >= btnPlay.x && mx <= btnPlay.x + btnPlay.w &&
                my >= btnPlay.y && my <= btnPlay.y + btnPlay.h)
            {
                init_game();
            }
            else if (state == STATE_GAMEOVER &&
                     mx >= btnRestart.x && mx <= btnRestart.x + btnRestart.w &&
                     my >= btnRestart.y && my <= btnRestart.y + btnRestart.h)
            {
                init_game();
            }
        }
    }
}

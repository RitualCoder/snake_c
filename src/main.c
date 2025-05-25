#include "sdl_utils.h"
#include "game.h"
#include "input.h"
#include "render.h"
#include "view.h"
#include <stdbool.h>
#include <SDL2/SDL.h>

#define UPDATE_MS 100

int main(void)
{
    if (!init_SDL())
        return 1;
    // Pas d'init_game() ici !
    Uint32 last_update = SDL_GetTicks();
    bool running = true;
    while (running)
    {
        switch (state)
        {
        case STATE_MENU:
            handle_input(&running);
            render_menu();
            break;

        case STATE_PLAYING:
        {
            handle_input(&running);
            Uint32 now = SDL_GetTicks();
            if (now - last_update >= UPDATE_MS)
            {
                update_game();
                last_update += UPDATE_MS;
                if (now - last_update >= UPDATE_MS)
                    last_update = now;
            }
            float t = (now - last_update) / (float)UPDATE_MS;
            if (t < 0)
                t = 0;
            else if (t > 1)
                t = 1;
            render_game(t);
            SDL_Delay(1);
            break;
        }

        case STATE_GAMEOVER:
            handle_input(&running);
            render_gameover();
            break;
        }
    }

    shutdown_SDL();
    return 0;
}

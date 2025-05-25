// src/main.c

#include "sdl_utils.h"
#include "game.h"
#include "input.h"
#include "render.h"
#include "view.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include <SDL2/SDL.h>
#include <stdbool.h>

#define UPDATE_MS 100

// Global utilisé en natif pour sortir de la boucle
static bool running = true;

// Prototype de la boucle principale
static void main_loop(void);

int main(void)
{
    if (!init_SDL())
        return 1;

    // Démarre en STATE_MENU, init_game() sera appelé par input

#ifdef __EMSCRIPTEN__
    // En WebAssembly : utilise requestAnimationFrame
    emscripten_set_main_loop(main_loop, 0, 1);
    // emscripten_set_main_loop ne revient jamais
    return 0;
#else
    // En natif : boucle tant que running == true
    while (running)
    {
        main_loop();
        SDL_Delay(1);
    }
    shutdown_SDL();
    return 0;
#endif
}

static void main_loop(void)
{
    static Uint32 last_update = 0;
    Uint32 now = SDL_GetTicks();

    // Gestion des entrées ; en natif handle_input(&running)
    // en WASM on ignore l’argument (signé dans input.c)
    handle_input(&running);

    switch (state)
    {
    case STATE_MENU:
        render_menu();
        break;

    case STATE_PLAYING:
        if (now - last_update >= UPDATE_MS)
        {
            update_game();
            last_update += UPDATE_MS;
            if (now - last_update >= UPDATE_MS)
                last_update = now;
        }
        render_game();
        break;

    case STATE_GAMEOVER:
        render_gameover();
        break;
    }
}

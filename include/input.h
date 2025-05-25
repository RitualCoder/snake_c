#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

// gère events et appelle init_game() si nécessaire, met *running=false pour quitter
void handle_input(bool *running);

#endif // INPUT_H

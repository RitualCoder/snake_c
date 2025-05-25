#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

// Gère les événements SDL et écrit *running=false si on doit quitter
void handle_input(bool *running);

#endif // INPUT_H

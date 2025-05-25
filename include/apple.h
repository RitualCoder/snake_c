#ifndef APPLE_H
#define APPLE_H

#include "snake.h"

extern Point apple;
// place la pomme dans une case libre du serpent
void spawn_apple(const Point snake[], int len);

#endif // APPLE_H

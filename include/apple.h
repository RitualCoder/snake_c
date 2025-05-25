#ifndef APPLE_H
#define APPLE_H

#include "snake.h"

extern Point apple;

// Place la pomme dans une case libre aléatoire
void spawn_apple(const Point snake[], int len);

#endif // APPLE_H

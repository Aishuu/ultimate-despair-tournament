#ifndef INIT_PLAYER_H
#define INIT_PLAYER_H

#include "game/game.h"

typedef char (*getThetaFunction)(const Game, void *);

getThetaFunction initTheDemos (const Game game, void * arg);
getThetaFunction initAishuu (const Game game, void * arg);

#endif // INIT_PLAYER_H

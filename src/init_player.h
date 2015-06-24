#ifndef INIT_PLAYER_H
#define INIT_PLAYER_H

#include "game/game.h"

typedef char (*getThetaFunction)(const Game);

getThetaFunction initTheDemos (const Game game);
getThetaFunction initAishuu (const Game game);

#endif // INIT_PLAYER_H

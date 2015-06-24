#ifndef __SRC_GAME_H
#define __SRC_GAME_H

#include "include.h"

struct Player {
    double x;
    double y;
    uint16_t theta; // angle en degres
};

typedef struct {
    uint8_t         cases [WIDTH][HEIGHT];
    struct Player   player1;
    struct Player   player2;
    uint8_t         won;
} * Game;

Game game_new_game ();
void game_free_game (Game game);
void game_update_game (Game game, char newTheta_1, char newTheta_2);

#endif // __SRC_GAME_H

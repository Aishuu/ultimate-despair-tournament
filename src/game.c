#include <stdlib.h>
#include <math.h>

#include "game.h"

Game game_new_game () {
    Game game = (Game) malloc (sizeof (*game));

    int i,j;
    for (i=0; i<WIDTH; i++)
        for (j=0; j<HEIGHT; j++)
            game->cases[i][j] = 0;

    do {
        game->player1.x     = rand () % WIDTH;
        game->player1.y     = rand () % HEIGHT;
        game->player1.theta = rand () % 360;
        game->player2.x     = rand () % WIDTH;
        game->player2.y     = rand () % HEIGHT;
        game->player2.theta = rand () % 360;
    } while (DIST(game->player1, game->player2) < MIN_INIT_DIST);

    game->cases[(int) game->player1.x][(int) game->player1.y] = 1;
    game->cases[(int) game->player2.x][(int) game->player2.y] = 2;

    game->won = 0;

    return game;
}

void game_free_game (Game game) {
    free (game);
}

void game_update_game (Game game, char newTheta_1, char newTheta_2) {
    game->player1.theta = (uint16_t) ((game->player1.theta + newTheta_1 * ((int) ANGULAR_SPEED)) % 360);
    game->player2.theta = (uint16_t) ((game->player2.theta + newTheta_2 * ((int) ANGULAR_SPEED)) % 360);

    int currentX = (int) game->player1.x;
    int currentY = (int) game->player1.y;
    game->player1.x += SPEED * cos(game->player1.theta * PI / 180);
    game->player1.y += SPEED * sin(game->player1.theta * PI / 180);
    int newX = (int) game->player1.x;
    int newY = (int) game->player1.y;

    if (abs(newX-currentX) > abs(newY-currentY)) {
        if (newX < currentX) {
            int tmp = newX;
            newX = currentX;
            currentX = tmp;
            tmp = newY;
            newY = currentY;
            currentY = tmp;
        }

        int A = 2*(newY - currentY);
        int B = A - 2*(newX - currentX);
        int P = A - (newX - currentX);

        currentX ++;
        while (currentX <= newX) {
            if (P < 0) {
                P += A;
            } else {
                if (newY > currentY)
                    currentY ++;
                else
                    currentY --;
                P += B;
            }
            if (game->cases[currentX % WIDTH][currentY % HEIGHT] != 0) {
                game->won = 2;
                break;
            }
            game->cases[currentX % WIDTH][currentY % HEIGHT] = 1;
            currentX ++;    
        }
    } else {
        if (newY < currentY) {
            int tmp = newX;
            newX = currentX;
            currentX = tmp;
            tmp = newY;
            newY = currentY;
            currentY = tmp;
        }

        int A = 2*(newX - currentX);
        int B = A - 2*(newY - currentY);
        int P = A - (newY - currentY);

        currentY ++;
        while (currentY <= newY) {
            if (P < 0) {
                P += A;
            } else {
                if (newX > currentX)
                    currentX ++;
                else
                    currentX --;
                P += B;
            }
            if (game->cases[currentX % WIDTH][currentY % HEIGHT] != 0) {
                game->won = 2;
                break;
            }
            game->cases[currentX% WIDTH][currentY % HEIGHT] = 1;
            currentY ++;    
        }
    }

    if (game->player1.x > WIDTH)
        game->player1.x -= WIDTH;
    if (game->player1.x < 0)
        game->player1.x += WIDTH;
    if (game->player1.y > HEIGHT)
        game->player1.y -= HEIGHT;
    if (game->player1.y < 0)
        game->player1.y += HEIGHT;

    currentX = (int) game->player2.x;
    currentY = (int) game->player2.y;
    game->player2.x += SPEED * cos(game->player2.theta * PI / 180);
    game->player2.y += SPEED * sin(game->player2.theta * PI / 180);
    newX = (int) game->player2.x;
    newY = (int) game->player2.y;

    if (abs(newX-currentX) > abs(newY-currentY)) {
        if (newX < currentX) {
            int tmp = newX;
            newX = currentX;
            currentX = tmp;
            tmp = newY;
            newY = currentY;
            currentY = tmp;
        }

        int A = 2*(newY - currentY);
        int B = A - 2*(newX - currentX);
        int P = A - (newX - currentX);

        currentX ++;
        while (currentX <= newX) {
            if (P < 0) {
                P += A;
            } else {
                if (newY > currentY)
                    currentY ++;
                else
                    currentY --;
                P += B;
            }
            if (game->cases[currentX % WIDTH][currentY % HEIGHT] != 0) {
                game->won ++;
                break;
            }
            game->cases[currentX % WIDTH][currentY % HEIGHT] = 2;
            currentX ++;    
        }
    } else {
        if (newY < currentY) {
            int tmp = newX;
            newX = currentX;
            currentX = tmp;
            tmp = newY;
            newY = currentY;
            currentY = tmp;
        }

        int A = 2*(newX - currentX);
        int B = A - 2*(newY - currentY);
        int P = A - (newY - currentY);

        currentY ++;
        while (currentY <= newY) {
            if (P < 0) {
                P += A;
            } else {
                if (newX > currentX)
                    currentX ++;
                else
                    currentX --;
                P += B;
            }
            if (game->cases[currentX % WIDTH][currentY % HEIGHT] != 0) {
                game->won ++;
                break;
            }
            game->cases[currentX % WIDTH][currentY % HEIGHT] = 2;
            currentY ++;    
        }
    }

    if (game->player2.x > WIDTH)
        game->player2.x -= WIDTH;
    if (game->player2.x < 0)
        game->player2.x += WIDTH;
    if (game->player2.y > HEIGHT)
        game->player2.y -= HEIGHT;
    if (game->player2.y < 0)
        game->player2.y += HEIGHT;
}

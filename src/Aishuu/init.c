#include "init_player.h"
#include "ANN.h"

#include <math.h>

#define N2(X,Y)    (sqrt((X)*(X)+(Y)*(Y)))

uint16_t distDirection (const Game game, uint16_t theta, int max) {
    int currentX = (int) game->player2.x;
    int currentY = (int) game->player2.y;
    int newX = currentX + (int) (max * cos(theta * PI / 180));
    int newY = currentY + (int) (max * sin(theta * PI / 180));

    if (newX != currentX || newY != currentY) {
        if (abs(newX-currentX) > abs(newY-currentY)) {
            if (newX > currentX) {
                int A = 2*(newY - currentY);
                int B = A - 2*(newX - currentX);
                int P = A - (newX - currentX);

                currentX ++;
                while (currentX < newX) {
                    if (P < 0) {
                        P += A;
                    } else {
                        if (newY > currentY)
                            currentY ++;
                        else
                            currentY --;
                        P += B;
                    }
                    if (CASE(currentX, currentY) != 0)
                        break;
                    currentX ++;    
                }
            } else {
                int A = 2*(newY - currentY);
                int B = A - 2*(currentX - newX);
                int P = A - (currentX - newX);

                currentX --;
                while (currentX > newX) {
                    if (P < 0) {
                        P += A;
                    } else {
                        if (newY > currentY)
                            currentY ++;
                        else
                            currentY --;
                        P += B;
                    }
                    if (CASE(currentX, currentY) != 0)
                        break;
                    currentX --;    
                }
            }
        } else {
            if (newY > currentY) {
                int A = 2*(newX - currentX);
                int B = A - 2*(newY - currentY);
                int P = A - (newY - currentY);

                currentY ++;
                while (currentY < newY) {
                    if (P < 0) {
                        P += A;
                    } else {
                        if (newX > currentX)
                            currentX ++;
                        else
                            currentX --;
                        P += B;
                    }
                    if (CASE(currentX, currentY) != 0)
                        break;
                    currentY ++;    
                }
            } else {
                int A = 2*(newX - currentX);
                int B = A - 2*(currentY - newY);
                int P = A - (currentY - newY);

                currentY --;
                while (currentY > newY) {
                    if (P < 0) {
                        P += A;
                    } else {
                        if (newX > currentX)
                            currentX ++;
                        else
                            currentX --;
                        P += B;
                    }
                    if (CASE(currentX, currentY) != 0)
                        break;
                    currentY --;    
                }
            }
        }
    } else
        return max;
    return max - ((int) N2 (currentX - (int) game->player2.x, currentY - (int) game->player2.y));
}

char getThetaAishuu (const Game game, void * arg) {
    ANN ann = (ANN) arg;

    int inputs [INPUTS];
    char outputs [OUTPUTS];

    int i;
    for (i=0; i<INPUTS; i++)
        inputs [i] = distDirection (game, game->player2.theta + 360*i/INPUTS, MAX_EDGE_VALUE);

    ANN_compute (ann, inputs, outputs);

    char r;

    if ((outputs[0] && outputs[1]) || (!outputs[0] && !outputs[1]))
        r = ((rand() % 2)*2) - 1;
    else
        r = outputs[0] ? -1 : 1;

    return r;
}

getThetaFunction initAishuu (const Game game, void * arg) {
    return getThetaAishuu;
}

#ifndef INCLUDE_H
#define INCLUDE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define WIDTH           600
#define HEIGHT          600

#define IMAGES_PER_SEC  60
#define MIN_INIT_DIST   100
#define SPEED           2
#define ANGULAR_SPEED   5

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define DIST_M(X, Y, Z) (MIN(abs((int)X - (int)Y), Z-abs(((int)X - (int)Y))))
#define DIST(p1, p2) (DIST_M(p1.x,p2.x,WIDTH) + DIST_M(p1.y,p2.y,HEIGHT))

static inline int mymodulo(int a, int b) {
    const int result = a % b;
    return result >= 0 ? result : result + b;
}

#define CASE(x,y) (game->cases[mymodulo(x,WIDTH)][mymodulo(y,HEIGHT)])

#define PI 3.14159265

#endif // INCLUDE_H

#ifndef __SRC_INCLUDE_H
#define __SRC_INCLUDE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>

#define WIDTH           600
#define HEIGHT          600

#define DELAY           60
#define MIN_INIT_DIST   100
#define SPEED           2
#define ANGULAR_SPEED   5

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define DIST_M(X, Y, Z) (MIN(abs((int)X - (int)Y), Z-abs(((int)X - (int)Y))))
#define DIST(p1, p2) (DIST_M(p1.x,p2.x,WIDTH) + DIST_M(p1.y,p2.y,HEIGHT))

#define PI 3.14159265

#endif // __SRC_INCLUDE_H

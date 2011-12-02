#ifndef PHYSICS_H
#define PHYSICS_H
#include "vector.h"
#include <stdio.h>
#define COEF_OF_REST 1
#include "ball.h"
int willCollide(BALL ball1 , BALL ball2);
void doCollision(BALL *ball1, BALL *ball2);
int  collideWall(BALL *ball , BALL wall[]);
int pocketIn(BALL *ball, BALL pocket[]);
#endif

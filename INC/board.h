#ifndef BOARD_H
#define BOARD_H
#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#define HOLE_RADIUS 0.06
#define LINE_HEIGHT 0.1
#define LINE_SIDE  0.18 
#define LINE_WIDTH 0.07
#define MID1CIRCLE_RADIUS 0.2
#define MID2CIRCLE_RADIUS 0.05
#define MID3CIRCLE_RADIUS 0.03
#define BOARD_SIDE 0.7
#define INNERCIRCLE_RADII 0.025
#define LINE_ARROW 0.5
#define ARROWCIRCLERADIUS 0.08
#define SMALLSIDE 0.03
void drawCoins(float x , float y, float radius , float thickness);
void drawArc(float x, float y, float radius, float initialangle, float finalangle);
void drawFillCircle(float x , float y, float radius);
void drawLineCircle(float x , float y , float radius);
void makeBoard();
#endif

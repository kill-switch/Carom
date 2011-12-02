#ifndef BALL_H
#define BALL_H
#include "vector.h"
typedef struct
{
	int label;
	vector pos;
	vector vel;
	float radius;
	float mass;
} BALL;

#endif

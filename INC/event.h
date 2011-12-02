#ifndef EVENT_H
#define EVENT_H
#include <string.h>
#include <stdio.h>

typedef struct
{
	int label;
	int ball1;
	int ball2;
	float time;
	char buffer1[80];// buffer for coppying the array
	char buffer2[80];
} event;
int isEqual(event a , event b);
#endif

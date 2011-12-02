#ifndef BALLQUEUE_H
#define BALLQUEUE_H

#include "ball.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>


typedef struct
{
	BALL arr[10];
	float time;
}ball_event;

typedef struct 
{
	ball_event *arr;
	int size;
	int head;
	int tail;
}ball_event_queue;

ball_event_queue *createQueue_ball(ball_event_queue *que, int size);
int isEmpty_ball(ball_event_queue *que);
int isFull_ball(ball_event_queue *que);
ball_event dequeue_ball(ball_event_queue *que,pthread_mutex_t arrmutex);
int enqueue_ball(ball_event_queue *que,ball_event a, pthread_mutex_t arrmutex);
void destroyQueue_ball(ball_event_queue *que);
ball_event top_ball(ball_event_queue *que);
void clearQueue_ball(ball_event_queue *que);
#endif

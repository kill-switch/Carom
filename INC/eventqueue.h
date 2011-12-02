#ifndef EVENTQUEUE_H
#define EVENTQUEUE_H
#include"event.h"
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef struct 
{
	event *arr;
	int size;
	int head;
	int tail;
}event_queue;
event_queue *createQueue(event_queue *que, int size);
int isEmpty(event_queue *que);
int isFull(event_queue *que);
event dequeue(event_queue *que,pthread_mutex_t arrmutex);
int enqueue(event_queue *que,event a, pthread_mutex_t arrmutex);
void destroyQueue(event_queue *que);
event top(event_queue *que);
void clearQueue(event_queue *que);
#endif

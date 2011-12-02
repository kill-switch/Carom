// BAll queue
#include "ballqueue.h"

// lib working fine :)
//working and ok
ball_event_queue *createQueue_ball(ball_event_queue *que, int size)
{
	que = (ball_event_queue *)malloc(sizeof(ball_event_queue));
	que->arr = (ball_event *)malloc(size*sizeof(ball_event));
	bzero(que->arr , size*sizeof(ball_event));
	que->size = size;
	que->head = 0;
	que->tail = 0;
	return que;
}


int isEmpty_ball(ball_event_queue *que)
{
	if(que->head == que->tail)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int isFull_ball(ball_event_queue *que)
{
	if(que->head ==(que->tail+1)%(que->size) )
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

ball_event dequeue_ball(ball_event_queue *que,pthread_mutex_t arrmutex)
{
	pthread_mutex_lock(&arrmutex);
	ball_event n = que->arr[que->head];		
	que->head = (que->head+1)%que->size;
	pthread_mutex_unlock(&arrmutex);
	return n;
}

int enqueue_ball(ball_event_queue *que,ball_event a, pthread_mutex_t arrmutex)
{// mutex for arrays
	int i;
	
		while(isFull_ball(que))
	{
	}
	pthread_mutex_lock(&arrmutex);
	que->arr[que->tail] =a;
	que->tail = (que->tail+1)%que->size;
	pthread_mutex_unlock(&arrmutex);
	return 0; 	
}

void destroyQueue_ball(ball_event_queue *que)
{
	free(que->arr);
	free(que);
}

ball_event top_ball(ball_event_queue *que)
{
	return que->arr[que->head];
}

void clearQueue_ball(ball_event_queue *que)
{
	int i;
	que->head = 0;
	que->tail = 0;
	bzero(que->arr , que->size*sizeof(ball_event));	
}

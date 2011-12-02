#include "eventqueue.h"
// lib working fine :)
//working and ok
event_queue *createQueue(event_queue *que, int size)
{
	que = (event_queue *)malloc(sizeof(event_queue));
	que->arr = (event *)malloc(size*sizeof(event));
	bzero(que->arr , size*sizeof(event));
	que->size = size;
	que->head = 0;
	que->tail = 0;
	return que;
}


int isEmpty(event_queue *que)
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

int isFull(event_queue *que)
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

event dequeue(event_queue *que,pthread_mutex_t arrmutex)
{
	pthread_mutex_lock(&arrmutex);
	event n = que->arr[que->head];		
	que->head = (que->head+1)%que->size;
	pthread_mutex_unlock(&arrmutex);
	return n;
}

int enqueue(event_queue *que,event a, pthread_mutex_t arrmutex)
{// mutex for arrays
	int i;
	
	for(i=que->head;i!=que->tail; i = (i+1)%que->size )
	{
		
		if(isEqual(a ,que->arr[i]) == 1)
		{
			printf("is same");
			return -1;
		}
	}
	while(isFull(que))
	{
	}
	pthread_mutex_lock(&arrmutex);
	que->arr[que->tail] =a;
	que->tail = (que->tail+1)%que->size;
	pthread_mutex_unlock(&arrmutex);
	return 0; 	
}

void destroyQueue(event_queue *que)
{
	free(que->arr);
	free(que);
}

event top(event_queue *que)
{
	return que->arr[que->head];
}

void clearQueue(event_queue *que)
{
	int i;
	que->head = 0;
	que->tail = 0;
	bzero(que->arr , que->size*sizeof(event));	
}

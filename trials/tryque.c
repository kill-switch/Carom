// tryeventque
#include "eventqueue.c"
#include <string.h>
#include <stdio.h>
pthread_mutex_t arrmutex = PTHREAD_MUTEX_INITIALIZER;

int main()
{
	event e;
	event a;
	e.time = 10;
	ball_event_queue *que;
	que = createQueue(que,25);
	printf("%d",enqueue(que,e,arrmutex));
	printf("%d",enqueue(que,a,arrmutex));
	destroyQueue(que);
}

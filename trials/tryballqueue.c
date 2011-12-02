// TRY BALL QUEUE
#include "ballqueue.c"


int main()
{
	ball_event a;
	a.time = 10;
	pthread_mutex_t arrmutex = PTHREAD_MUTEX_INITIALIZER;
	
	ball_event_queue *b;
	b = createQueue_ball(b,2);
	
	printf("%d\n",isEmpty_ball(b));
	enqueue_ball(b,a,arrmutex);
	printf("%d\n",isFull_ball(b));
	printf("%f\n",top_ball(b).time);
	printf("%d\n",isEmpty_ball(b));
	dequeue_ball(b,arrmutex);
	printf("%d\n",isEmpty_ball(b));	
}	







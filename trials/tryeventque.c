#include"eventqueue.c"


int main()
{
	event_queue *que;
	que = createQueue(que,5);
	pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
	event e;
	int i =0;
	while(!isFull(que))
	{
		e.label = i;
			enqueue(que,e,queue_mutex);
			printf("%d %d\n",que->head,que->tail);
		i++;
		if( getchar() == 'a')
		{
			dequeue(que,queue_mutex);
			getchar();
		}
		if(isEmpty(que))
		{
			printf("empty");
		}
			
	}
}

#include"physicthread.c"

	BALL wall[4];
	BALL pocket[4];
	BALL coins[10];

float gameclk;
void physicstryupdate(int value)
{
	BALL b;
	event e;
	ball_event be;
	int i;
	while(!isEmpty(physicsque))
	{
		printf("%d\n",physicsque->tail);
		printf("%d\n",physicsque->head);
		//printf("here");		
		e = top(physicsque);
		if(e.time > gameclk)
		{
			break;	
		}

		printf("%d %d %d %f",e.label,e.ball1,e.ball2,e.time);
		bcopy(e.buffer1,&b,sizeof(BALL));
		printf("ball b %f",b.pos.x);
		getchar();
		dequeue(physicsque, arrmutex);
	}
	/*be = top_ball(ballque);
	
		while(be.time <gameclk)
		{
			printf("ball event missed\n");
			dequeue_ball(ballque,ballmutex);
			be = top_ball(ballque);
		}
	
		if(be.time == gameclk)
		{
			for(i = 0;i<10;i++)
			{
				coins[i] = be.arr[i];
			}
		}
		
		if(be.time>gameclk)
		{
			printf("gameclock running ahead of physics");
		}

	*/
	gameclk +=2.5;
	printf("%f\n",gameclk);
	getchar();
	printf("%f %f %f\n",coins[0].pos.x , coins[0].pos.y,coins[0].vel.x);
	printf("%f %f %f\n",coins[1].pos.x , coins[1].pos.y,coins[1].vel.x);
	physicstryupdate(value);
	
}

int main()
{

	wall[0].pos	.x = 0;
	wall[1].pos.x = 100;
	wall[2].pos.y = 0;
	wall[3].pos.y = 100;
	pocket[0].pos.x = 5;
	pocket[0].pos.y = 5;
	pocket[1].pos.x = 5;
	pocket[1].pos.y = 95;
	pocket[2].pos.x = 95;
	pocket[2].pos.y = 95;
	pocket[3].pos.x = 95;
	pocket[3].pos.y = 5;
	pocket[0].radius = 5;
	pocket[1].radius = 5;
	pocket[2].radius = 5;
	pocket[3].radius = 5;
	coins[0].pos.x = 50;
	coins[0].pos.y = 50;
	coins[0].pos.z = 50;
	coins[0].vel.x = 0.1;
	coins[0].vel.y = 0;
	coins[0].vel.z = 0;
	coins[0].radius = 5;
	coins[0].mass = 1;
	coins[1].pos.x = 75;
	coins[1].pos.y = 50;
	coins[1].pos.z = 50;
	coins[1].vel.x = -0.1;
	coins[1].vel.y = 0;
	coins[1].vel.z = 0;
	coins[1].radius = 5;
	coins[1].mass = 1;	
	startSim(coins,wall,pocket);
	physicstryupdate(1);
	while(1)
	{
	}
}



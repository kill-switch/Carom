
#include "eventqueue.h"
#include "ballqueue.h"
#include "physics.h"
#include <stdio.h>
#include <pthread.h>
#define COEF_OF_FRIC 0.00009
#define GRAV 9.87
#define PHYTICK 0.25
#define GAMETICK 2.5
#define NOOFCOINS 6
// label phypocketin 1 collide phywall 2 collision 3


event_queue *physicsque;
ball_event_queue *ballque;
int event_size = 50;
BALL phycoins[10];
BALL phywall[4];
BALL phypocket[4];
pthread_t carethread;
pthread_mutex_t arrmutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t ballmutex = PTHREAD_MUTEX_INITIALIZER;
char runphytrd;
char isRunningphy[10];

//working and ok include friction only
//func working ok
void *takeCare2(void *in)
{	
	int i;
	int j;
	float gameclk;
	event eve;
	ball_event beve;
	float phyclk = 0;
	int tookplace = -1;
	int allstop = 0;
	vector v1;
	for(i=0;i<=9;i++)
	{
		isRunningphy[i]=1;
	}
	
	while(runphytrd == 1)
	{
		phyclk +=PHYTICK;
		gameclk +=PHYTICK;

		//ALL BALL STOP ROUTINE -START
		allstop = 0;
		for(i=0;i<NOOFCOINS;i++)
		{
			if(isRunningphy[i] == 1)
			{
				allstop =1;
			}
		
		}
		
		if(allstop == 0)
		{
			eve.time = gameclk;
			eve.ball1 = 0;
			eve.ball2 = 0;
			eve.label = 6;
			//label 6 is for all stop events;
			while(isFull(physicsque))
			{
				if(runphytrd == 0)
				{
					break;
				}
				// donothing here it waits for the que to become empty :(
			}			
			enqueue(physicsque, eve, arrmutex);
			runphytrd =0;
			break;
		}
		
		
		for(i=0 ; i< NOOFCOINS;i++)
		{
			if(isRunningphy[i]==0)
			{
				continue;
			}
			if(phycoins[i].vel.x ==0 && phycoins[i].vel.y == 0)
			{
				isRunningphy[i] == 0;
			}
			else
			{
				v1 = subVector(phycoins[i].vel,multConstant(phycoins[i].vel , PHYTICK*phycoins[i].mass*GRAV*COEF_OF_FRIC/modValue(phycoins[i].vel)));
			}
			if(dotProduct(v1,phycoins[i].vel)<=0 || isRunningphy[i]==0)
			{
				phycoins[i].vel.x = 0;
				phycoins[i].vel.y =0;
				isRunningphy[i]=0;
			}
			if(phycoins[i].vel.x ==0 && phycoins[i].vel.y == 0)
			{
				isRunningphy[i] == 0;
			}
			else
			{
				phycoins[i].vel = v1;
				phycoins[i].pos = subVector(phycoins[i].pos,multConstant(phycoins[i].vel , PHYTICK*PHYTICK*GRAV*COEF_OF_FRIC/(2*modValue(phycoins[i].vel))));
			}
	
			phycoins[i].pos = addVector(phycoins[i].pos,multConstant(phycoins[i].vel,PHYTICK));
		}
		
		for(i=0;i<NOOFCOINS ; i++)
		{
			while(isFull(physicsque))
			{
				//printf("is full");
				//getchar();
				if(runphytrd == 0)
				{
					//break;
				}
			
			}
			tookplace = pocketIn(&phycoins[i], phypocket);
			if(tookplace >=0)
			{// ball phypocketed ??
				eve.time = gameclk;
				eve.ball1 = i;
				eve.ball2 = tookplace;
				eve.label = 1;
				bcopy( &phycoins[i] ,eve.buffer1 , sizeof(BALL));
				enqueue(physicsque, eve, arrmutex);
				bzero(eve.buffer1,255);
			}
			tookplace = collideWall(&phycoins[i], phywall);
			if(tookplace >=0)
			{// ball collide phywall
				eve.time = gameclk;
				eve.ball1 = i;
				eve.ball2 = tookplace;
				eve.label = 2;
				
				bcopy( &phycoins[i] ,eve.buffer1 , sizeof(BALL));
				if(enqueue(physicsque, eve, arrmutex)==-1)
				{
					//getchar();
				}
				bzero(eve.buffer1,255);
			}	
		}
		
		for(i=0;i<NOOFCOINS;i++)
		{
			for(j=0;j<NOOFCOINS;j++)
			{
				if(i==j)
				{
					continue;
				}
	
				else
				{
					if(tookplace = willCollide(phycoins[i], phycoins[j]))
					{// ball collide ball
						eve.time = gameclk;
						eve.ball1 = i;
						isRunningphy[i]=1;
						eve.ball2 = j;
						isRunningphy[j]=1;
						eve.label = 3;
						doCollision(&phycoins[i], &phycoins[j]);
						bcopy( &phycoins[i] ,eve.buffer1 , sizeof(BALL));
						bcopy( &phycoins[j] ,eve.buffer2 , sizeof(BALL));
						while(isFull(physicsque))
						{
							if(runphytrd == 0)
							{
								break;
							}
								// donothing here it waits for the que to become empty :(
						}
						
						enqueue(physicsque, eve, arrmutex);
						bzero(eve.buffer1,255);
						bzero(eve.buffer2,255);
					}
				}	
			}
		}
		if(phyclk == GAMETICK)
		{
			phyclk -=GAMETICK;
			beve.time = gameclk;
			for(i=0;i<10;i++)
			{
				beve.arr[i] = phycoins[i];
			}
			while(isFull_ball(ballque))
			{
				if(runphytrd == 0)
				{
					break;
				}
							
			}
			enqueue_ball(ballque,beve,ballmutex);
			eve.time = gameclk;
			eve.ball1 = 0;
			eve.ball2 = 0;
			eve.label = 0;
			//label zero is to sinc event ques;
			while(isFull(physicsque))
			{
				if(runphytrd == 0)
				{
					break;
				}
				// donothing here it waits for the que to become empty :(
			}			
			enqueue(physicsque, eve, arrmutex);
		}				
	}
	pthread_exit(NULL);	
}


event_queue *startSim(BALL cn[],BALL wl[],BALL hl[])
{
	int iret;
	runphytrd = 1;
	physicsque = createQueue(physicsque, 100);
	ballque = createQueue_ball(ballque,100);
	int i;
	for(i = 0; i<=9;i++)
	{
		phycoins[i]=cn[i];
	}
	
	for(i = 0; i<=3;i++)
	{
		phywall[i]=wl[i];
	}
	
	for(i = 0; i<=3;i++)
	{
		phypocket[i]=hl[i];
	}
	
	
	iret = pthread_create(&carethread , NULL,takeCare2, NULL);
	if(iret != 0)
	{
			printf("error in takecare thread create");
			return NULL;
	}
	return physicsque;		
		
}



int stopSim()
{
	runphytrd =0;
	pthread_join(carethread,NULL);
	return 1;
}

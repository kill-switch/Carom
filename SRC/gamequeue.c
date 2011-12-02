//genenral event queue
#include "board.h"
#include"physicthread.c"
#include"langame.h"
#define MAXBLACK 2
#define QUEEN_COIN_NO 5 
#define VEL_MAX 0.05


float gameclock ;
event_queue *queue;
event_queue *rulesque;
pthread_mutex_t queue_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t rules_mutex = PTHREAD_MUTEX_INITIALIZER;
int gamepause =0;
char phydone;
pthread_t enterPhyThread;
pthread_t enterNetThread;
BALL coins[10];
BALL pocket[4];
BALL wall[4];
int chance;
char runphy;
int playerno;
int playerchance;
char gametype = 1;
char isAI[4];


void handleKeypress(unsigned char key, int x, int y);

void ghostBall(BALL target[],int targetcoin,BALL coins[],BALL pocket[])
{
	bzero(target,4*sizeof(BALL));
	vector v1;
	vector vball;
	int i;
	int j;
	char isCorrect = 0;
	float y;
	
	for(i=0;i<4;i++)
	{
		isCorrect = 1;
		v1 =subVector(pocket[i].pos,coins[targetcoin].pos);
		for(j=1;j<NOOFCOINS;j++)
		{
			if(j == targetcoin)
		 	{
				continue;
			}
			
			if(pocket[i].pos.x>coins[targetcoin].pos.x && pocket[i].pos.y >coins[targetcoin].pos.y)
			{
				if(coins[j].pos.x > coins[targetcoin].pos.x && pocket[j].pos.y >coins[targetcoin].pos.y)
				{
					y = distanceLinePoint(v1,coins[targetcoin].pos,coins[j].pos);
					if(y < coins[targetcoin].radius + coins[j].radius)
					{
						isCorrect = 0;
						
					}					
				}
			}
			if(pocket[i].pos.x<coins[targetcoin].pos.x && pocket[i].pos.y >coins[targetcoin].pos.y)
			{
				if(coins[j].pos.x < coins[targetcoin].pos.x && pocket[j].pos.y >coins[targetcoin].pos.y)
				{
					y = distanceLinePoint(v1,coins[targetcoin].pos,coins[j].pos);
					if(y < coins[targetcoin].radius + coins[j].radius)
					{
						isCorrect = 0;
						
					}					
				}
			}
			if(pocket[i].pos.x>coins[targetcoin].pos.x && pocket[i].pos.y <coins[targetcoin].pos.y)
			{
				if(coins[j].pos.x > coins[targetcoin].pos.x && pocket[j].pos.y <coins[targetcoin].pos.y)
				{
					y = distanceLinePoint(v1,coins[targetcoin].pos,coins[j].pos);
					if(y < coins[targetcoin].radius + coins[j].radius)
					{
						isCorrect = 0;
						
					}					
				}
			}
			if(pocket[i].pos.x<coins[targetcoin].pos.x && pocket[i].pos.y <coins[targetcoin].pos.y)
			{
				if(coins[j].pos.x < coins[targetcoin].pos.x && pocket[j].pos.y <coins[targetcoin].pos.y)
				{
					y = distanceLinePoint(v1,coins[targetcoin].pos,coins[j].pos);
					if(y < coins[targetcoin].radius + coins[j].radius)
					{
						isCorrect = 0;
						
					}					
				}
			}
		}
		if(isCorrect == 0)
		{
			target[i].pos.x =9999;
			target[i].pos.y = 9999;
			target[i].pos.z = 9999;
		
		}
		else
		{
			target[i].pos = subVector(coins[targetcoin].pos,multConstant(v1,(coins[targetcoin].radius +coins[0].radius)/modValue(v1)));
			vball = multConstant(v1,sqrt(2*(GRAV*COEF_OF_FRIC)/modValue(v1)));
			target[i].vel = multConstant(vball,(2*coins[targetcoin].mass + coins[0].mass)/(coins[0].mass*(1+COEF_OF_REST)));//1.1 here is the correction factor
		}
	}
}

vector velToGhost(BALL ghost,vector currentPos)
{
	vector v;
	vector vfinal;
	vector distance;
	float dot;
	float tempmod;
	char isCorrect;
	int i;
	
	distance = subVector(ghost.pos , currentPos);
	if(modValue(distance) == 0)
	{
		return ghost.vel;
	}
	
	dot = dotProduct(distance,ghost.vel)/(modValue(distance)*modValue(ghost.vel));
	if(dot <= 0)
	{
		v.x =0;
		v.y =0;
		v.z =0;
		return v;
	}
	isCorrect =1;
	for(i =1;i<NOOFCOINS;i++)
	{
		if(distanceLinePoint(distance,currentPos,coins[i].pos) < coins[i].radius + coins[0].radius)
		{
			if(dotProduct(subVector(coins[i].pos,currentPos),distance)*dotProduct(subVector(coins[i].pos,ghost.pos),distance) < 0)
			{
				isCorrect = 0;
			}
		
		}
	}
	if(isCorrect == 0)
	{
		v.x =0;
		v.y =0;
		v.z =0;
		return v;
	}
	tempmod = modValue(ghost.vel)/dot;
	tempmod = sqrt(tempmod*tempmod + 2*GRAV*COEF_OF_FRIC*modValue(distance));
	v = multConstant(distance , (1.1)*tempmod/modValue(distance));//1.1 is safety factor
	return v;
}


BALL aiHunter(int targetcoin)
{
	vector posprev;
	vector mostfitpos;
	vector mostfitvel;
	vector distance;
	float maxfitness = 0;
	float fitness = 0;
	BALL b;
	bzero(&b,sizeof(BALL));
	b.pos.z =0;
	BALL target[4];
	int i;
	char foundOne = 0;
	ghostBall(target,targetcoin,coins,pocket);
	char goneOneWay =0;
	while(1)
	{
		for(i= 0;i<4;i++)	
		{
			b.pos.x = coins[0].pos.x;
			b.pos.y = coins[0].pos.y;
			if(target[i].pos.x == 9999 && target[i].pos.y == 9999)
			{
				continue;
			}
			b.vel = velToGhost(target[i],b.pos);
			if(modValue(b.vel) > VEL_MAX)
			{
				//printf("GOING BEYOND GAME VEL");
			}
			if(b.vel.x == 0 && b.vel.y == 0)
			{
				continue;
			}
			distance = subVector(coins[targetcoin].pos,coins[0].pos);
			fitness = dotProduct(distance,b.vel);///(modValue(distance)*modValue(b.vel));
			fitness = fitness/(modValue(distance)*modValue(b.vel)*modValue(b.vel));
			if(fitness < 0)
			{
				fitness = -1*fitness;
			}
			if(fitness > maxfitness)
			{
				maxfitness = fitness;
				foundOne = 1;
				mostfitpos.x = b.pos.x;
				mostfitpos.y = b.pos.y;
				mostfitvel.x = b.vel.x;
				mostfitvel.y = b.vel.y;
			}
		}
		posprev.x = coins[0].pos.x;
		posprev.y = coins[0].pos.y;
		if(goneOneWay == 0)
		{
			//printf("BEEN HERE AT LEAST THAT MANY TIMES\n");
			handleKeypress('l',1,1);
		}
		if(goneOneWay == 1)
		{
			//printf("BEEN HERE AT LEAST THAT HOW MANY TIMES\n");
			handleKeypress('j',1,1);
		}
		if(posprev.x == coins[0].pos.x && posprev.y == coins[0].pos.y)
		{
			if(goneOneWay == 0)
			{
				goneOneWay =1;
			}
			else
			{
				break;
			}
		}
	}
	if(foundOne == 1)
	{
		//printf("MOST FIT POS : %f %f \n",mostfitpos.x,mostfitpos.y);
		b.pos = mostfitpos;
		b.vel = mostfitvel;
	}
	return b;
}



BALL aiChance()
{
	BALL b;
	int targetcoin;
	bzero(&b,sizeof(BALL));
	int i;
	
	if(playerchance == 0 || playerchance == 2)
	{
		if(coins[QUEEN_COIN_NO].pos.x != 9999 && coins[QUEEN_COIN_NO].pos.y != 9999)
		{
			targetcoin = QUEEN_COIN_NO;
			b = aiHunter(5);
		}
		if(b.vel.x == 0 && b.vel.y == 0)
		{
			for(i=1;i<NOOFCOINS;i++)
			{
				if(coins[i].label == 1 && coins[i].pos.x != 9999 && coins[i].pos.y != 9999)
				{
					b = aiHunter(i);
					if(b.vel.x != 0 && b.vel.y != 0)
					{
						break;
					}
				}
			}
		}
	}
	if(playerchance == 1 || playerchance == 3)
	{
		if(coins[QUEEN_COIN_NO].pos.x != 9999 && coins[QUEEN_COIN_NO].pos.y != 9999)
		{
			targetcoin = QUEEN_COIN_NO;
			b = aiHunter(5);
		}
		if(b.vel.x == 0 && b.vel.y == 0)
		{
			for(i=1;i<NOOFCOINS;i++)
			{
				if(coins[i].label == 2 && coins[i].pos.x != 9999 && coins[i].pos.y != 9999)
				{
					b = aiHunter(i);
					if(b.vel.x != 0 && b.vel.y != 0)
					{
						break;
					}
				}
			}
		}
	}
	return b;
}


BALL returnAi(int aiLevel)
{
	int rand = random()%100;
	char isCorrect =1;
	BALL b;
	if(aiLevel == 1)
	{//easy
		if(rand < 75)
		{
			isCorrect =0;
		}
	}
	if(aiLevel == 2)
	{//easy
		if(rand < 50)
		{
			isCorrect =0;
		}
	}
	if(aiLevel == 3)
	{//easy
		if(rand < 25)
		{
			isCorrect =0;
		}
	}
	if(aiLevel == 4)
	{//easy
		isCorrect = 1;
	}
	if(isCorrect ==1)
	{
		return aiChance();
	
	}
	if(isCorrect == 0)
	{
		pocket[0].pos.x = 0.0f;
		pocket[0].pos.y = -BOARD_SIDE + HOLE_RADIUS;
		pocket[1].pos.x = BOARD_SIDE - HOLE_RADIUS;
		pocket[1].pos.y = 0.0f;
		pocket[2].pos.x = 0.0f;
		pocket[2].pos.y =  BOARD_SIDE - HOLE_RADIUS;
		pocket[3].pos.x = -BOARD_SIDE + HOLE_RADIUS;
		pocket[3].pos.y = 0.0f;
		b = aiChance();
		pocket[0].pos.x = -BOARD_SIDE + HOLE_RADIUS;
		pocket[0].pos.y = -BOARD_SIDE + HOLE_RADIUS;
		pocket[1].pos.x = BOARD_SIDE - HOLE_RADIUS;
		pocket[1].pos.y = -BOARD_SIDE + HOLE_RADIUS;
		pocket[2].pos.x = BOARD_SIDE - HOLE_RADIUS;
		pocket[2].pos.y =  BOARD_SIDE - HOLE_RADIUS;
		pocket[3].pos.x = -BOARD_SIDE + HOLE_RADIUS;
		pocket[3].pos.y = BOARD_SIDE -HOLE_RADIUS;	
		return b;
	}
	return aiChance();
}


//working and ok
vector relocateStriker()
{
	vector v;
	if(gametype == 1)
	{
		if(playerchance == 0)
		{
			v.x = 0.0f;
			v.y = -BOARD_SIDE + LINE_HEIGHT + LINE_WIDTH/2;	
		}
		if(playerchance == 1)
		{
			v.x = 0.0f;
			v.y = BOARD_SIDE - LINE_HEIGHT - LINE_WIDTH/2;	
		}
	}	
	
	if(gametype == 2)
	{
		if(playerchance == 0)
		{
			v.x = 0.0f;
			v.y = -BOARD_SIDE + LINE_HEIGHT + LINE_WIDTH/2;
		}
		
		if(playerchance == 1)
		{
			v.y = 0.0f;
			v.x = BOARD_SIDE - LINE_HEIGHT - LINE_WIDTH/2;
		
		}
		if(playerchance == 2)
		{
			v.x = 0.0f;
			v.y = BOARD_SIDE - LINE_HEIGHT - LINE_WIDTH/2;	
		}
		if(playerchance == 3)
		{
			v.y = 0.0f;
			v.x = -BOARD_SIDE + LINE_HEIGHT + LINE_WIDTH/2;
		}
	}
	return v;
}

vector findValidPosition(float Radius,BALL coins[],BALL wall[],BALL pocket[])
{
	char isCorrect = 0;
	vector v;
	v.z =0;
	float y;
	int i;
	while(isCorrect == 0)
	{
		isCorrect = 1;
		v.x = (random()%100)/100.0;
		v.y = (random()%100)/100.0;
		for(i= 0 ;i<10;i++)
		{
			 y = modValue(subVector(v, coins[i].pos));
			 if(y < Radius + coins[i].radius)
			 {
			 	isCorrect = 0;
			 }
		}
		if(v.x - wall[0].pos.x < Radius )
		{				
			isCorrect =0;
		}
		if(wall[1].pos.x - v.x  < Radius )
		{				
			isCorrect =0;
		}
		if(v.y - wall[2].pos.y < Radius )
		{				
			isCorrect =0;
		}
		if(wall[3].pos.y - v.y  < Radius )
		{				
			isCorrect =0;
		}
		for(i = 0;i<4;i++)
		{
			y = modValue(subVector(v, pocket[i].pos));
			if(y < pocket[i].radius)
			{
				isCorrect = 0;
			}
		}			
	}
	return v;
}

vector findValidCentralPosition(float Radius,BALL coins[],BALL wall[],BALL pocket[])
{
	char isCorrect = 0;
	vector v;
	v.z =0;
	v.x = 0;
	v.y = 0;
	float y;
	int i;
	char isNotCorrectCount = 0;
	while(isCorrect == 0)
	{
		isCorrect = 1;
		
		for(i= 0 ;i<6;i++)
		{
			 y = modValue(subVector(v, coins[i].pos));
			 if(y < Radius + coins[i].radius)
			 {
			 	isCorrect = 0;
			 }
		}
		if(v.x - wall[0].pos.x < Radius )
		{				
			isCorrect =0;
		}
		if(wall[1].pos.x - v.x  < Radius )
		{				
			isCorrect =0;
		}
		if(v.y - wall[2].pos.y < Radius )
		{				
			isCorrect =0;
		}
		if(wall[3].pos.y - v.y  < Radius )
		{				
			isCorrect =0;
		}
		for(i = 0;i<4;i++)
		{
			y = modValue(subVector(v, pocket[i].pos));
			if(y < pocket[i].radius)
			{
				isCorrect = 0;
			}
		}
		if(isCorrect == 0)
		{
		
			if(isNotCorrectCount == 0)
			{
				v.x = -1*v.x;
				isNotCorrectCount++;
			}
			if(isNotCorrectCount == 1)
			{
				v.y = -1*v.y;
				isNotCorrectCount++;
			}
			if(isNotCorrectCount == 2)
			{
				v.x = -1*v.x;
				isNotCorrectCount++;
			}
			if(isNotCorrectCount == 3)
			{
				isNotCorrectCount =0;
				v.y = -1*v.y;
				v.y +=Radius;
				v.x +=Radius;
			}
		}		
	}
	return v;
}


int replaceCoins(int label)
{
	int i = 0;
	//getchar();
	for(i = 0;i <6 ; i++)
	{
		if(coins[i].label == label)
		{
			if(coins[i].pos.x == 9999 && coins[i].pos.y == 9999)
			{
				coins[i].pos = findValidCentralPosition(coins[i].radius,coins,wall,pocket);
				return 1;	
			}
		}
	}
	return 0;
}



int gameRules()
{
	static int noofwhiteballs = MAXBLACK;
	static int noofblackballs = MAXBLACK;
	static int team1CoinsDue =0;
	static int team2CoinsDue =0;
	static char isQueenIn = 0;
	static char willQueenbein =0;
	char isQueenTakenInThisChance = 0;
	char ownCoinIn = 0;
	char strikerIn = 0;
	int temp;
	int currentChance = playerchance;
	int noOfCoinsToBePlaced = 0;
	event e;
	BALL bl;
	int i;
	
	//Event Segreagation
	while(!isEmpty(rulesque))
	{
		
		e =dequeue(rulesque,rules_mutex);
		if(e.label == 1)
		{
			//balls gone in
			bcopy(e.buffer1,&bl,sizeof(BALL));
			if(bl.label == 1)
			{
				//here
				noofwhiteballs--;
				if(gametype == 1 && playerchance == 0)
				{
					ownCoinIn = 1;
				}
				if(gametype == 2 && (playerchance == 0 || playerchance == 2) )
				{
					ownCoinIn = 1;
				}
			}
			if(bl.label == 2)
			{
			
				noofblackballs--;
				if(gametype == 1 && playerchance == 1)
				{
					ownCoinIn = 1;
				}
				if(gametype == 2 && (playerchance == 1 || playerchance == 3) )
                {
                	ownCoinIn = 1;
                                                              
				}
			}
			if(bl.label == 3)
			{
				//queen in
				willQueenbein =1;
				isQueenTakenInThisChance = 1;
			}
			if(bl.label == 0)
			{
				strikerIn = 1;	
			}
		}
	}
	


	if(willQueenbein == 1)
	{
		if(isQueenTakenInThisChance == 1)
		{
			if(ownCoinIn == 1)
			{
				
				if(strikerIn == 1)
				{
					if(playerchance == 0|| playerchance ==2)
					{
						team1CoinsDue +=2;
					}
					if(playerchance == 1 || playerchance == 3)
					{
						team2CoinsDue +=2;
					}
					//place two coins
				}
				
				if(playerchance == 0 || playerchance == 2)
				{
					isQueenIn = 1;
				}
				if(playerchance == 1 || playerchance ==3)
				{
					isQueenIn = 2;
				}
				if(playerno == playerchance)
				{
					chance = 1;
				}
			}
			if(ownCoinIn == 0)
			{
				if(strikerIn == 1)
				{
					if(playerchance == 0|| playerchance ==2)
					{
						team1CoinsDue +=2;
					}
					if(playerchance == 1 || playerchance == 3)
					{
						team2CoinsDue +=2;
					}//place two coins in 
				}
				if(playerno == playerchance)
				{
					chance = 1;
				}
			}
		
		
		}
		
		if(isQueenTakenInThisChance == 0)
		{
			if(ownCoinIn == 1)
			{
				if(strikerIn == 1)
				{
					if(playerchance == 0|| playerchance ==2)
					{
						team1CoinsDue +=2;
					}
					if(playerchance == 1 || playerchance == 3)
					{
						team2CoinsDue +=2;
					}
 	
				}
				if(playerchance == 0|| playerchance ==2)
				{
					isQueenIn = 1;
				}
				if(playerchance == 1 || playerchance == 3)
				{
					isQueenIn = 2;
				}
				if(playerno == playerchance)
				{
					chance = 1;
				}
				willQueenbein = 0;
			}
			if(ownCoinIn == 0)
			{
				replaceCoins(3);
				if(strikerIn == 1)
				{
					if(playerchance == 0|| playerchance ==2)
					{
						team1CoinsDue +=1;
					}
					if(playerchance == 1 || playerchance == 3)
					{
						team2CoinsDue +=1;
					}
				}
				willQueenbein = 0;
				if(gametype == 1)
				{
					playerchance= (playerchance+1)%2;
				}
				if(gametype == 2)
				{
					playerchance= (playerchance+1)%4;	
				}		
		
				if(playerno == playerchance)
				{
					chance = 1;
				}
				willQueenbein = 0;
				//place Queen	
			}
		}
	}
	else
	{	
		if(ownCoinIn==1 && strikerIn == 0)
		{
			//printf("owncoinin chance");
			//simple case of my coin in redo chance
			if(playerchance == playerno)
			{
				chance = 1;
			}
		}
	
		if(ownCoinIn == 1 && strikerIn == 1)
		{
			if(playerchance == 0|| playerchance ==2)
			{
				team1CoinsDue +=2;
			}
			if(playerchance == 1 || playerchance == 3)
			{
				team2CoinsDue +=2;
			}
			
			if(playerchance == playerno)
			{
			
				chance = 1;
			}
		}
		
		if(ownCoinIn==0 )
		{
			if(strikerIn == 1)
			{
					
				if(playerchance == 0|| playerchance ==2)
				{
						team1CoinsDue +=1;
				}
				if(playerchance == 1 || playerchance == 3)
				{
						team2CoinsDue +=1;
				}
						
				
		
			}
			//place Coin and Place Coins 
			//simple case of my coin in redo chance
		
			if(gametype == 1)
			{
				playerchance= (playerchance+1)%2;
			}
			if(gametype == 2)
			{
				playerchance= (playerchance+1)%4;	
			}		
			
			if(playerno == playerchance)
			{
				chance = 1;
			}
			
		}	
	}
	
	if(team1CoinsDue > 0)
	{
		temp =0;
		if(noofwhiteballs < MAXBLACK)
		{
			temp = MAXBLACK - noofwhiteballs;
			noofwhiteballs = MAXBLACK;
			team1CoinsDue -=temp;
			if(team1CoinsDue < 0)
			{
				noofwhiteballs = noofwhiteballs + team1CoinsDue;
				team1CoinsDue = 0;
			}
		}
		for(i= 0; i<temp;i++)
		{
			replaceCoins(1);
			//place white coins
		}
			
	}
	if(team2CoinsDue > 0)
	{
		if(noofblackballs < MAXBLACK)
		{
			temp = MAXBLACK - noofwhiteballs;
			noofblackballs = MAXBLACK;
			team2CoinsDue -=temp;
			if(team2CoinsDue < 0)
			{
				noofblackballs = noofblackballs + team2CoinsDue;
				team2CoinsDue = 0;
			}
		}
		for(i= 0; i<temp;i++)
		{
			replaceCoins(2);
		}
			
	}
	
	printf("COINS : %d %d %d %d\n",team1CoinsDue,team2CoinsDue,noofwhiteballs,noofblackballs);
	if(noofwhiteballs == 0 && team1CoinsDue == 0 && isQueenIn != 0)
	{
		playerchance = -1;
		gamepause = 1;
	}
	if(noofblackballs == 0 && team2CoinsDue == 0 && isQueenIn != 0)
	{
		playerchance = -2;
		gamepause = 1;
	}
}

// this function is working fine
void *enterPhyData(void *in)
{
	event_queue *physicque;
	event e;
	runphytrd = 0;
	while(1)
	{
		
		runphy =1;
		
		while(runphytrd == 0)
		{		
		}
		physicsque = startSim(coins,wall,pocket);
		
		while(runphytrd == 1)
		{
			while(!isEmpty(physicsque) && runphy == 1)
			{	
				phydone=0;		
				e = top(physicsque);
				if(e.time < gameclock)
				{
					gameclock = e.time;
				
				}
				while(e.time > gameclock)
				{
					phydone = 1;
				}
				while(isFull(queue))
				{
				}
			
				dequeue(physicsque, arrmutex);
				enqueue(queue ,e,queue_mutex);
			}
			if(runphy == 1)
			{
				phydone =1;
			}
			else
			{
				stopSim();
			}
		}
	}
	
}



// func working fine
void *enterNetData(void *in)
{
	event e;
	char buffer[256];
	int n;
	char c;
	while(1)
	{
		bzero(buffer,255);
		n = recieveData(buffer,256);
		bcopy(buffer, &e,sizeof(event));
		if(n>0)
		{
			bcopy(&e,buffer , sizeof(event));
			if(e.time == playerno)
			{
				continue;
			}
			if(e.label == 4)
			{
				bcopy(e.buffer1,&coins[e.ball1],sizeof(BALL));
				if(e.ball2 == 1)
				{
					runphytrd = 1;
					chance = 0;
					gamepause = 0;	
				}
				if(playerno == 0)
				{
					sendData(&e,sizeof(event),-1);
				}
			}
			if(e.label == 5)
			{
				gamepause =1 - gamepause;
				if(playerno == 0)
				{
					sendData(&e,sizeof(event),-1);
				}
			}
			if(e.label == 7)
			{
				chance = 1;
				coins[0].pos.x = 0.0;
				coins[0].pos.y = -BOARD_SIDE + LINE_HEIGHT + LINE_WIDTH/2;
			}
		}	
	}
}


void startqueue()
{	
	gameclock = 0;
	rulesque = createQueue(rulesque, 100);
	queue = createQueue(queue , 100);	
	int iret;
	iret = pthread_create(&enterPhyThread,NULL,enterPhyData,NULL);
	if(iret !=0)
	{
		printf("error");
	}	
	iret = pthread_create(&enterNetThread,NULL,enterNetData,NULL);
	if(iret !=0)
	{
		printf("error");
	}	
}


void update2(int value)
{
	int i;
	BALL b;
	event e;
	ball_event be;
	vector v1;
	char c = 0;
	if(chance == 0 && gamepause == 0)
	{
		runphytrd = 1;
		gameclock+=GAMETICK;
		while(!isEmpty(queue) && phydone == 1)
		{// do something 
			e = dequeue(queue, queue_mutex);
			if(e.label == 1)
			{//pocketin
				enqueue(rulesque,e,rules_mutex);
			}
			
			if(e.label == 0)
			{
				// command to sinc ballques
				be = dequeue_ball(ballque,ballmutex);
				for(i=0;i<10;i++)
				{
				
					coins[i]=be.arr[i];
				}
			}
			if(e.label==6)
			{
				runphy =0;
				runphytrd = 0;
				stopSim();
				clearQueue(queue);
				chance = 2;
				gameclock =0;
				runphy = 1;
				gameRules();		
				coins[0].pos = relocateStriker();						
			}
		}
		
	}
	glutPostRedisplay();
	glutTimerFunc(GAMETICK , update2 , 0);
}

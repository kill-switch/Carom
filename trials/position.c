#ifndef PHYSICS_H
#define PHYSICS_H
#include "physics.c"
#endif
#include <stdlib.h>

vector findValidPositon(float Radius,BALL coins[],BALL wall[],BALL pocket[])
{
	char isCorrect = 0;
	vector v;
	float y;
	while(isCorrect == 0)
	{
		isCorrect = 1;
		v.x = random(100)/100.0;
		v.y = random(100)/100.0;
		for(i= 0 ;i<10;i++)
		{
			 y = modValue(subVector(v, coins[i].pos));
			 if(y > Radius + coins[i].radius)
			 {
			 	isCorrect = 0;
			 }
		}
		if(v.x - wall[0].pos.x < Radius && v.x - wall[0].pos.x>0)
		{				
			isCorrect =0;
		}
		if(wall[1].pos.x - v.x  < Radius && wall[1].pos.x - v.x >0)
		{				
			isCorrect =0;
		}
		if(v.y - wall[2].pos.y < Radius && v.y - wall[2].pos.y>0)
		{				
			isCorrect =0;
		}
		if(wall[3].pos.y - v.y  < Radius && wall[3].pos.y - v.y >0)
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

int replaceCoins(int label)
{
	for(i = 0;i <10 ; i++)
	{
		if(coins[i].label == label)
		{
			if(coins[i].pos.x == 9999 && coins[i].pos.y == 9999)
			{
				coins[i].pos = findValidPosition(coins[i].radius,coins,wall,pocket)
				return 1;	
			}
		}
	}
	return 0;
}

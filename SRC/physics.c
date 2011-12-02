// physics
#include "physics.h"

//all funcs are working ok
int willCollide(BALL ball1 , BALL ball2)
{
	float y = modValue(subVector(ball1.pos, ball2.pos));
	if(y <= ball1.radius + ball2.radius)
	{
		if(dotProduct(subVector(ball1.pos, ball2.pos), subVector(ball1.vel,ball2.vel)) < 0)
		{
			return 1;
		}
	}
	return 0;
}



void doCollision(BALL *ball1, BALL *ball2)
{
	vector temp = subVector(ball1->pos, ball2->pos);// common normals of twoball shaped objects
	vector cmnormal;
	cmnormal = multConstant(temp , 1/modValue(temp));
	vector v1nom ;
	v1nom = multConstant(cmnormal , dotProduct(ball1->vel , cmnormal));
	vector v2nom ;
	v2nom = multConstant(cmnormal , dotProduct(ball2->vel , cmnormal));
	vector v1tan = subVector(ball1->vel, v1nom);
	vector v2tan = subVector(ball2->vel, v2nom);

	temp = multConstant(addVector(multConstant(v1nom , ball1->mass),multConstant(v2nom , ball2->mass)), 1/(ball1->mass + ball2->mass));	
	vector temp2 = addVector(temp , multConstant(subVector(v1nom , v2nom), ball1->mass*COEF_OF_REST/(ball1->mass+ball2->mass)));
	vector temp3 = addVector(temp , multConstant(subVector(v2nom , v1nom), ball2->mass*COEF_OF_REST/(ball1->mass+ball2->mass)));
	
	v2nom = temp2;
	v1nom = temp3;
	
	ball1->vel = addVector(v1tan , v1nom);
	ball2->vel = addVector(v2tan , v2nom);
	
}



int  collideWall(BALL *ball , BALL wall[])
{

		if(ball->pos.x - wall[0].pos.x <= ball->radius )//x1wall
		{
			if(ball->vel.x < 0)
			{
				//pthread_mutex_lock(&ballmutex);
				ball->vel.x = -COEF_OF_REST*ball->vel.x;
				//pthread_mutex_unlock(&ballmutex);
				return 0;
			}
		}
		
	if(ball->pos.x - wall[1].pos.x >= -ball->radius )//y1wall
		{
			if(ball->vel.x > 0)
			{
				//pthread_mutex_lock(&ballmutex);
				ball->vel.x = -COEF_OF_REST*ball->vel.x;
				//pthread_mutex_unlock(&ballmutex);
				return 1;
			}
		}
	
	if(ball->pos.y - wall[2].pos.y <= ball->radius )//x1wall
		{
			if(ball->vel.y < 0)
			{
				//pthread_mutex_lock(&ballmutex);
				ball->vel.y = -COEF_OF_REST*ball->vel.y;
				//pthread_mutex_unlock(&ballmutex);
				return 2;
			}
		}
	
	if(ball->pos.y - wall[3].pos.y >= -ball->radius )//x1wall
		{
			if(ball->vel.y > 0)
			{
				//pthread_mutex_lock(&ballmutex);
				ball->vel.y = -COEF_OF_REST*ball->vel.y;
				//pthread_mutex_unlock(&ballmutex);
				return 3;
			}
		}
	return -1;
}
	



int pocketIn(BALL *ball, BALL pocket[])
{
	int i;
	for(i=0;i<4 ;i++)
	{
		if( modValue(subVector(ball->pos, pocket[i].pos)) <= pocket[i].radius)
		{
			//pthread_mutex_lock(&ballmutex);
			ball->vel = multConstant(ball->vel , 0);
			ball->pos.x = 9999;
			ball->pos.y = 9999;
			ball->pos.z = 9999;
			//pthread_mutex_unlock(&ballmutex);
			return i;
		}		
	}
	return -1;
}

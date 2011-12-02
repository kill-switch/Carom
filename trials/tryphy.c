// tryphysics

#include "physics.c"
#include  <stdio.h>

int main()
{
	BALL ball1;
	BALL ball2;
	ball1.label = "ball1";
	ball2.label = "ball2";
	BALL hole[4];
	ball1.pos.x = 55;
	ball1.pos.y = 0;
	ball1.pos.z = 0;
	ball1.radius = 5;
	ball1.vel.x = 0.1;
	ball1.vel.y = 0;
	ball1.vel.z = 0;
	ball2.pos.x = 65;
	ball2.pos.y = 0;
	ball2.pos.z = 0;
	ball2.radius = 5;
	ball2.vel.x = -0.1;
	ball2.vel.y = 0;
	ball2.vel.z = 0;
	ball1.mass= 10;
	ball2.mass= 10;
	 
	
	hole[0].pos.x = 2;
	hole[0].pos.y = 0;	
	hole[0].radius = 3;
	printf("%d\n",willCollide(ball1 , ball2));
doCollision(&ball1 , &ball2);
	
	
	
	printf("%f\n",ball2.vel.x );
	printf("%f\n",ball1.vel.x );
	printf("%f\n",ball1.vel.y );
	printf("%f\n",ball1.vel.z );
	printf("%f\n",ball1.pos.x );
	printf("%f\n",ball1.pos.y );
	printf("%f\n",ball1.pos.z );
	//printf("%f\n",subVector(a,b).y);
}

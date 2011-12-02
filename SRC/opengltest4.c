#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "gamequeue.c" 
#define RADIUS_STRIKER 0.04
void drawScene();
void update2(int value);
float xang;
float yang;
float zang;
float ang = 0.0f;
float velocity = 0.01f;
void handleKeypressUser(unsigned char key,int x, int y)
{
	event e;
	if(gametype == 1)
	{
		if(playerno == 0)
		{
			switch(key)
			{
				case 108:
				if( coins[0].pos.x < BOARD_SIDE - LINE_SIDE-LINE_WIDTH/2)
				{
					coins[0].pos.x += 0.01f ;
					glutPostRedisplay();
				}
				break;
				case 106:
				if( coins[0].pos.x > -BOARD_SIDE + LINE_SIDE+LINE_WIDTH/2)
				{
					coins[0].pos.x -= 0.01f ;
					glutPostRedisplay();
				}
				break;		
			}
		}
		if(playerno == 1)
		{
			switch(key)
			{
				case 106:
				if( coins[0].pos.x < BOARD_SIDE - LINE_SIDE-LINE_WIDTH/2)
				{
					coins[0].pos.x += 0.01f ;
					glutPostRedisplay();
				}
				break;
				case 108:
				if( coins[0].pos.x > -BOARD_SIDE + LINE_SIDE+LINE_WIDTH/2)
				{
					coins[0].pos.x -= 0.01f ;
					glutPostRedisplay();
				}
				break;		
			}
		}		
	}
	if(gametype == 2)
	{
		if(playerno == 0)
		{
			switch(key)
			{
				case 108:
				if( coins[0].pos.x < BOARD_SIDE - LINE_SIDE-LINE_WIDTH/2)
				{
					coins[0].pos.x += 0.01f ;
					glutPostRedisplay();
				}
				break;
				case 106:
				if( coins[0].pos.x > -BOARD_SIDE + LINE_SIDE+LINE_WIDTH/2)
				{
					coins[0].pos.x -= 0.01f ;
					glutPostRedisplay();
				}
				break;		
			}
		}
		if(playerno == 1)
		{
			switch(key)
			{
				case 108:
				if( coins[0].pos.y < BOARD_SIDE - LINE_SIDE-LINE_WIDTH/2)
				{
					coins[0].pos.y += 0.01f ;
					glutPostRedisplay();
				}
				break;
				case 106:
				if( coins[0].pos.y > -BOARD_SIDE + LINE_SIDE+LINE_WIDTH/2)
				{
					coins[0].pos.y -= 0.01f ;
					glutPostRedisplay();
				}
				break;		
			}
		}
		if(playerno == 2)
		{
			switch(key)
			{
				case 106:
				if( coins[0].pos.x < BOARD_SIDE - LINE_SIDE-LINE_WIDTH/2)
				{
					coins[0].pos.x += 0.01f ;
					glutPostRedisplay();
				}
				break;
				case 108:
				if( coins[0].pos.x > -BOARD_SIDE + LINE_SIDE+LINE_WIDTH/2)
				{
					coins[0].pos.x -= 0.01f ;
					glutPostRedisplay();
				}
				break;		
			}
		}		
		if(playerno == 3)
		{
			switch(key)
			{
				case 106:
				if( coins[0].pos.y < BOARD_SIDE - LINE_SIDE-LINE_WIDTH/2)
				{
					coins[0].pos.y += 0.01f ;
					glutPostRedisplay();
				}
				break;
				case 108:
				if(coins[0].pos.y > -BOARD_SIDE + LINE_SIDE+LINE_WIDTH/2)
				{
					coins[0].pos.y -= 0.01f ;
					glutPostRedisplay();
				}
				break;		
			}
		}
	}
	e.label = 4;
	e.ball1 = 0;
	e.ball2 = 0;
	e.time = playerno;
	bcopy(&coins[0],e.buffer1,sizeof(BALL));
	sendData(&e,sizeof(event),-1);
}


		
void handleKeypress(unsigned char key, int x, int y)
{
	event e;
	char isCorrect = 0;
	float willBeCorrect =0;
	int i;
	vector v;
	vector vorig;
	float yx;
	//BALL target[4];
	BALL b;
	vector redCircle[8];
	redCircle[0].x = BOARD_SIDE-LINE_HEIGHT - LINE_WIDTH/2;
	redCircle[0].y =  BOARD_SIDE-LINE_SIDE - LINE_WIDTH/2;
	redCircle[0].z = 0;
	redCircle[1].x = -BOARD_SIDE+LINE_HEIGHT + LINE_WIDTH/2 ;
	redCircle[1].y =  BOARD_SIDE-LINE_SIDE - LINE_WIDTH/2;
	redCircle[1].z = 0;
	redCircle[2].x =-BOARD_SIDE+LINE_HEIGHT + LINE_WIDTH/2;
	redCircle[2].y =  -BOARD_SIDE+LINE_SIDE + LINE_WIDTH/2;
	redCircle[2].z = 0;
	redCircle[3].x = BOARD_SIDE-LINE_HEIGHT - LINE_WIDTH/2;
	redCircle[3].y =  -BOARD_SIDE+LINE_SIDE + LINE_WIDTH/2;
	redCircle[3].z = 0;
	redCircle[4].x =BOARD_SIDE-LINE_SIDE - LINE_WIDTH/2;
	redCircle[4].y = BOARD_SIDE-LINE_HEIGHT - LINE_WIDTH/2;
	redCircle[4].z = 0;
	redCircle[5].x =BOARD_SIDE-LINE_SIDE - LINE_WIDTH/2;
	redCircle[5].y = -BOARD_SIDE+LINE_HEIGHT + LINE_WIDTH/2;
	redCircle[5].z = 0;
	redCircle[6].x = -BOARD_SIDE+LINE_SIDE + LINE_WIDTH/2;
	redCircle[6].y = -BOARD_SIDE+LINE_HEIGHT + LINE_WIDTH/2;
	redCircle[6].z = 0;
	redCircle[7].x = -BOARD_SIDE+LINE_SIDE + LINE_WIDTH/2;
	redCircle[7].y = BOARD_SIDE-LINE_HEIGHT - LINE_WIDTH/2;
	redCircle[7].z = 0;
	
	switch(key)
	{
		case 97:// akey
			if(xang > -90)
			{
				xang = xang -1.0f;
			}
			glutPostRedisplay();
			break;
		case 100:// 27 refers to the case of esc
			if(xang < 90)
			{
				xang = xang +1.0f;
			}
			glutPostRedisplay();
			break;
		case 119:
			if(yang <90)
			{
				yang = yang +1.0f;
			}
			glutPostRedisplay();
			break;
		case 115:
			if(yang > -90)
			{
				yang = yang -1.0f;
			}
			glutPostRedisplay();
			break;
		case 113:// a key
			zang = zang +1.0f;
			glutPostRedisplay();
			break;
		case 101:// a key
			zang = zang -1.0f;
			glutPostRedisplay();
			break;
		case 105:
			ang +=1.0f ;
			glutPostRedisplay();
			break;
		case 107:
			ang -=1.0f ;
			glutPostRedisplay();
			break;
		case 109:
			if(chance == 1 && velocity<VEL_MAX)
			{
				velocity += 0.01f ;
				glutPostRedisplay();
			}
			break;
		case 110:
			if(chance == 1 && velocity>0.0f)
			{
				velocity -= 0.01f ;
				glutPostRedisplay();
			}
			break;
		case 111:
			if(chance != 0)
			{
				//ghostBall(target,1,coins,pocket);
				b = aiChance();
				coins[0].pos.x = b.pos.x;
				coins[0].pos.y = b.pos.y;
				coins[0].vel.x = b.vel.x;
				coins[0].vel.y = b.vel.y;
				if(b.vel.x == 0 && b.vel.y == 0)
				{
					printf("I COUILDNT DO IT\n");
				}
				e.label = 4;
				e.ball1 = 0;
				e.ball2 = 1;
				e.time = playerno;
				bcopy(&coins[0],e.buffer1,sizeof(BALL));
				runphytrd=1;
				sendData(&e,sizeof(event),-1);
				chance =0;
			}
			break;
		case 112:
			if(chance != 0  && isAI[playerchance] !=0 && playerno == 0)
			{
			//ghostBall(target,1,coins,pocket);
				b = returnAi(isAI[playerchance]);	
				coins[0].pos.x = b.pos.x;
				coins[0].pos.y = b.pos.y;
				coins[0].vel.x = b.vel.x;
				coins[0].vel.y = b.vel.y;
				if(b.vel.x == 0 && b.vel.y == 0)
				{
					printf("I COUILDNT DO IT\n");
				}
				e.label = 4;
				e.ball1 = 0;
				e.ball2 = 1;
				e.time = playerno;
				bcopy(&coins[0],e.buffer1,sizeof(BALL));
				runphytrd=1;
				sendData(&e,sizeof(event),-1);
				chance =0;
			}
			if(chance == 1 && (isAI[0] !=0 && playerno != 0))
			{// let me say you wnt to run ai on a different pc than the server
				b = returnAi(isAI[playerchance]);	
				coins[0].pos.x = b.pos.x;
				coins[0].pos.y = b.pos.y;
				coins[0].vel.x = b.vel.x;
				coins[0].vel.y = b.vel.y;
				if(b.vel.x == 0 && b.vel.y == 0)
				{
					printf("I COUILDNT DO IT\n");
				}
				e.label = 4;
				e.ball1 = 0;
				e.ball2 = 1;
				e.time = playerno;
				bcopy(&coins[0],e.buffer1,sizeof(BALL));
				runphytrd=1;
				sendData(&e,sizeof(event),-1);
				chance =0;			
			}
			break;
		case 32:
			if(chance == 1)
			{
				coins[0].vel.x = -velocity*sin(ang*22.0f/7.0f/180.0f);
				coins[0].vel.y = velocity*cos(ang*22.0f/7.0f/180.0f);
				e.label = 4;
				e.ball1 = 0;
				e.ball2 = 1;
				e.time = playerno;
				bcopy(&coins[0],e.buffer1,sizeof(BALL));
				runphytrd=1;
				sendData(&e,sizeof(event),-1);
				chance =0;
			}
			break;
		case 104:
			if(gametype == 1)
			{
				zang = 180*playerno;
			}
			if(gametype == 2)
			{
				zang = 90*playerno;
			}
			xang = 0.0f;
			yang = 0.0f;
			break;
		case 27:
			e.label = 5;
			e.time = playerno;
			sendData(&e,sizeof(event),-1);
			gamepause = 1-gamepause;
			break;
	}
	// the below Danc is only to take care of the fact tha t balls doesnot overlap an existing ball in collision
	if(chance == 1 || isAI[playerchance] != 0)
	{
		vorig = coins[0].pos;
		willBeCorrect = 0;
		while(isCorrect == 0)
		{
			v = coins[0].pos;
			handleKeypressUser(key,x,y);
			if(v.x == coins[0].pos.x && v.y == coins[0].pos.y )
			{
				
				//printf("here\n ");
				coins[0].pos.x = vorig.x;
				coins[0].pos.y = vorig.y;
				break;
			}
			v = coins[0].pos;
			isCorrect = 1;
			for(i= 1 ;i<6;i++)
			{
				 yx = modValue(subVector(v, coins[i].pos));
				 if(yx <=coins[0].radius  + coins[i].radius)
				 {
				 	isCorrect = 0;
				 }
			}
			for(i= 1 ;i<8;i++)
			{
				 yx = modValue(subVector(v, redCircle[i]));
				 if(yx <coins[0].radius  + INNERCIRCLE_RADII && yx != 0)
				 {
				 	if(yx <= 0.005)
				 	{
				 		coins[0].pos.x = redCircle[i].x;
				 		coins[0].pos.y = redCircle[i].y;	
				 	}
				 	else
				 	{
				 		isCorrect = 0;
				 	}
				 }
			}				
		}
	}
}


void initRendering()
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glEnable(GL_DEPTH_TEST);
	glClearColor(0.0f, 0.8f, 0.9f , 1.0f);
	//glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
	glLoadIdentity();
}

void handleResize(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)w/(double)h, 1.0, 200.0);
}

void drawScene()
{	// frames are of -1 to 1 in initial vies point
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glTranslatef(0.0f,0.0f,-2.0f);
	glColor3f(0.0f,0.0f,0.0f);
	glRasterPos2f(-0.7f,0.7f);
	const unsigned char *sr = "IF U WANT AI TO TAKE TURNS PLEASE PRESS 'p'";
	glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,sr);
	glPopMatrix();
	if(gamepause == 1)
	{
		glPushMatrix();
		glTranslatef(0.0f,0.0f,-2.0f);
		
		glColor3f(0.0f,0.0f,0.0f);
		glBegin(GL_QUADS);
		glVertex3f(-0.2f,-0.2f,-0.01f);
		glVertex3f(-0.2f,0.2f,-0.01f);
		glVertex3f(0.2f,0.2f,-0.01f);
		glVertex3f(0.2f,-0.2f,-0.01f);
		glEnd();
		glColor3f(1.0f,1.0f,1.0f);
		glRasterPos2f(-0.16f,0.15f);
		const unsigned char *st = "Game Paused";
		if(playerchance == -1)
		{
			st = "TEAM1 WINS";
		}
		if(playerchance == -2)
		{
			st = "TEAM2 WINS";
		}

		glutBitmapString(GLUT_BITMAP_TIMES_ROMAN_24,st);
		glPopMatrix();
	}
	
	if(chance == 1)
	{
		glBegin(GL_QUADS);// sides of black
		glVertex3f(-1.0f,velocity*10,-3.0f);
		glVertex3f(-1.01f,velocity*10,-3.0f);
		glVertex3f(-1.01f,0.0f,-3.0f);
		glVertex3f(-1.0f,0.0f,-3.0f);
		glEnd();
	
	}
	glPushMatrix();// this is the frame of the carrom board
	glTranslatef(0.0f, 0.0f, -3.0f);
	glRotatef(-xang,1.0f, 0.0f , 0.0f);
	glRotatef(-yang,0.0f, 1.0f, 0.0f);
	glRotatef(-zang,0.0f, 0.0f, 1.0f);
	makeBoard();
	glEnd();
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 0.0f);
	glTranslatef(coins[0].pos.x, coins[0].pos.y ,0.003f);
	drawCoins(0.0f , 0.0f, 0.04f , 0.03f);
	if(chance ==1)
	{
		glColor3f(0.0f, 0.0f, 1.0f);
		glPushMatrix();
		glRotatef(ang , 0.0f , 0.0f, 1.0f);
		glBegin(GL_LINES);
		glVertex3f(0.0f, RADIUS_STRIKER, 0.0f);
		glVertex3f(0.0f, RADIUS_STRIKER + 0.2f , 0.0f);
		glEnd();
		glPopMatrix();
	}
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(coins[1].pos.x, coins[1].pos.y ,0.003f);
	drawCoins(0.0f , 0.0f, 0.04f , 0.03f);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(coins[2].pos.x, coins[2].pos.y ,0.003f);
	drawCoins(0.0f , 0.0f, 0.04f , 0.03f);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(coins[3].pos.x, coins[3].pos.y ,0.003f);
	drawCoins(0.0f , 0.0f, 0.04f , 0.03f);
	glPopMatrix();
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 1.0f);
	glTranslatef(coins[4].pos.x, coins[4].pos.y ,0.003f);
	drawCoins(0.0f , 0.0f, 0.04f , 0.03f);
	glPopMatrix();
	glPushMatrix();
	glColor3f(0.0f, 1.0f, 1.0f);
	glTranslatef(coins[5].pos.x, coins[5].pos.y ,0.003f);
	drawCoins(0.0f , 0.0f, 0.04f , 0.03f);
	glPopMatrix();
	glPopMatrix();
 	glutSwapBuffers();
}



void (* update)(int value);

int game(int argc, char** argv, int player)
{	
	char *carrom;
	playerno = player;
	playerchance =0;
	if(playerno == 0)
	{
		chance = 1;
		carrom = "server";
		update = &update2;
	}
	else
	{	
		chance = 2;
		carrom = "client";
		update = &update2;
	}	
		
	gamepause = 0;
	wall[0].pos.x = -BOARD_SIDE;
	wall[1].pos.x = BOARD_SIDE;
	wall[2].pos.y = -BOARD_SIDE;
	wall[3].pos.y = BOARD_SIDE;
	pocket[0].pos.x = -BOARD_SIDE + HOLE_RADIUS;
	pocket[0].pos.y = -BOARD_SIDE + HOLE_RADIUS;
	pocket[1].pos.x = BOARD_SIDE - HOLE_RADIUS;
	pocket[1].pos.y = -BOARD_SIDE + HOLE_RADIUS;
	pocket[2].pos.x = BOARD_SIDE - HOLE_RADIUS;
	pocket[2].pos.y =  BOARD_SIDE - HOLE_RADIUS;
	pocket[3].pos.x = -BOARD_SIDE + HOLE_RADIUS;
	pocket[3].pos.y = BOARD_SIDE -HOLE_RADIUS;
	pocket[0].radius = HOLE_RADIUS;
	pocket[1].radius = HOLE_RADIUS;
	pocket[2].radius = HOLE_RADIUS;
	pocket[3].radius = HOLE_RADIUS;
	coins[0].label = 0;
	coins[0].pos.x = 2*0.04;//BOARD_SIDE - 2*HOLE_RADIUS -3*0.04;//0.0;
	coins[0].pos.y =  -BOARD_SIDE + LINE_HEIGHT + LINE_WIDTH/2;//BOARD_SIDE - 2*HOLE_RADIUS -3*0.04;//-BOARD_SIDE + LINE_HEIGHT + LINE_WIDTH/2;
	coins[0].pos.z = 0;
	coins[0].vel.x = 0.0;
	coins[0].vel.y = 0.0;
	coins[0].vel.z = 0;
	coins[0].radius = 0.04;
	coins[0].mass = 1;
	coins[1].label = 1;
	coins[1].pos.x = -BOARD_SIDE + 2*HOLE_RADIUS +0.04;//0.0;
	coins[1].pos.y = -BOARD_SIDE + 2*HOLE_RADIUS +0.04;//0.0;
	coins[1].pos.z = 0;
	coins[1].vel.x = 0.0;
	coins[1].vel.y = 0.0;
	coins[1].vel.z = 0;
	coins[1].radius = 0.04;
	coins[1].mass = 1;
	coins[2].label = 1;
	coins[2].pos.x = -BOARD_SIDE + LINE_HEIGHT + LINE_WIDTH/2;
	coins[2].pos.y = 0.08;//0.0f;
	coins[2].pos.z = 0;
	coins[2].vel.x = 0.0;
	coins[2].vel.y = 0.0;
	coins[2].vel.z = 0;
	coins[2].radius = 0.04;
	coins[2].mass = 1;
	coins[3].label = 2;
	coins[3].pos.x = -0.08f;
	coins[3].pos.y = BOARD_SIDE - LINE_HEIGHT - LINE_WIDTH/2;
	coins[3].pos.z = 0;
	coins[3].vel.x = 0.0;
	coins[3].vel.y = 0.0;
	coins[3].vel.z = 0;
	coins[3].radius = 0.04;
	coins[3].mass = 1;
	coins[4].label = 2;
	coins[4].pos.x = BOARD_SIDE - LINE_HEIGHT - LINE_WIDTH/2;
	coins[4].pos.y = -0.08f;
	coins[4].pos.z = 0;
	coins[4].vel.x = 0.0;
	coins[4].vel.y = 0.0;
	coins[4].vel.z = 0;
	coins[4].radius = 0.04;
	coins[4].mass = 1;
	coins[5].label = 3;
	coins[5].pos.x = BOARD_SIDE - 2*HOLE_RADIUS -0.04;//0.0;
	coins[5].pos.y = BOARD_SIDE - 2*HOLE_RADIUS -0.04;//2*RADIUS_STRIKER;
	coins[5].pos.z = 0;
	coins[5].vel.x = 0.0;
	coins[5].vel.y = 0.0;
	coins[5].vel.z = 0;
	coins[5].radius = 0.04;
	coins[5].mass = 1;
	coins[6].pos.x = 0;
	coins[6].pos.y =0;
	xang = 0.0f;
	yang =0.0f;
	
	if(gametype == 1)
	{
		zang = 180*playerno;
	}
	if(gametype == 2)
	{
		zang = 90*playerno;
	}
	startqueue();
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize( 800, 800);
	glutCreateWindow(carrom);
	initRendering();
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(handleKeypress);
	glutReshapeFunc(handleResize);
	glutTimerFunc(GAMETICK , update , 0);
 	glutMainLoop();
 	return 0;	
}

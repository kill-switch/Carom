//gl board
#include "board.h"

void drawCoins(float x , float y, float radius , float thickness)
{
	glPushMatrix();
	glTranslatef(x,y,0.0f);
	float angle=0.0f;
	glBegin(GL_POLYGON);
	for(angle=0;angle < 2*3.15 ; angle= angle + 0.01f)
	{
		glVertex3f( radius*cos(angle) ,  radius*sin(angle) , 0.0f);
	}
	glEnd();
	glBegin(GL_POLYGON);
	for(angle=0;angle < 2*3.15 ; angle= angle + 0.01f)
	{
		glVertex3f( radius*cos(angle) ,  radius*sin(angle) , 0.0f + thickness);
	}
	glEnd();
	for(angle=0;angle < 2*3.15 ; angle= angle + 0.01f)
	{
		glBegin(GL_QUADS);
		glVertex3f( radius*cos(angle) ,  radius*sin(angle) , 0.0f + thickness);
		glVertex3f( radius*cos(angle) ,  radius*sin(angle) , 0.0f );
		glVertex3f( radius*cos(angle+0.01) ,  radius*sin(angle+0.01) , 0.0f );
		glVertex3f( radius*cos(angle+0.01) ,  radius*sin(angle+0.01) , 0.0f + thickness);
		glEnd();	
	}
	glPopMatrix();
}


void drawArc(float x, float y, float radius, float initialangle, float finalangle)
{
	float angle;
	glBegin(GL_LINE_STRIP);
	for(angle=initialangle;angle <= finalangle ; angle= angle + 1.0f)
	{
		glVertex3f(x + radius*cos(3.14*angle/180.0) , y + radius*sin(3.14*angle/180.0) , 0.0f);
	}
	glEnd();
}

void drawFillCircle(float x , float y, float radius)
{
	float angle=0.0f;
	glBegin(GL_POLYGON);
	for(angle=0;angle < 2*3.15 ; angle= angle + 0.001f)
	{
		glVertex3f(x + radius*cos(angle) , y + radius*sin(angle) , 0.0f);
	}
	glEnd();
}

void drawLineCircle(float x , float y , float radius)
{
	float angle=0.0f;
	glBegin(GL_LINE_STRIP);
	for(angle=0;angle <= 2*3.14 ; angle= angle + 0.001f)
	{
		glVertex3f(x + radius*cos(angle) , y + radius*sin(angle) , 0.0f);
	}
	glEnd();
}

void makeBoard()
{
	glBegin(GL_QUADS);// lower black part
	glColor3f(222.0f/255.0f, 184.0f/255.0f, 135.0f/255.0f);
	glVertex3f(-0.8f,-0.8f,-0.1f);
	glVertex3f(0.8f,-0.8f,-0.1f);
	glVertex3f(0.8f,0.8f,-0.1f);
	glVertex3f(-0.8f,0.8f,-0.1f);
	glEnd();
	// all the below code is just to handle the ends ( to make it look good while rotations)
	glBegin(GL_QUADS);// sides of black
	glColor3f(222.0f/255.0f, 184.0f/255.0f, 135.0f/255.0f);
	glVertex3f(0.8f,-0.8f,0.04f);
	glVertex3f(0.8f,-0.8f,-0.1f);
	glVertex3f(0.8f,0.8f,-0.1f);
	glVertex3f(0.8f,0.8f,0.04f);
	glEnd();
	glBegin(GL_QUADS);// sides of black
	glVertex3f(-0.8f,-0.8f,0.04f);
	glVertex3f(-0.8f,-0.8f,-0.1f);
	glVertex3f(-0.8f,0.8f,-0.1f);
	glVertex3f(-0.8f,0.8f,0.04f);
	glEnd();
	glBegin(GL_QUADS);// sides of black
	glVertex3f(-0.8f,0.8f,0.04f);
	glVertex3f(-0.8f,0.8f,-0.1f);
	glVertex3f(0.8f,0.8f,-0.1f);
	glVertex3f(0.8f,0.8f,0.04f);
	glEnd();
	glBegin(GL_QUADS);// sides of black
	glVertex3f(-0.8f,-0.8f,0.04f);
	glVertex3f(-0.8f,-0.8f,-0.1f);
	glVertex3f(0.8f,-0.8f,-0.1f);
	glVertex3f(0.8f,-0.8f,0.04f);
	glEnd();
	glBegin(GL_QUADS);// middle orange part
	glColor3f(1.0f, 165.0f/255.0f, 0.0f);
	glVertex3f(-BOARD_SIDE,-BOARD_SIDE,0.0f);
	glVertex3f(BOARD_SIDE,-BOARD_SIDE,0.0f);
	glVertex3f(BOARD_SIDE,BOARD_SIDE,0.0f);
	glVertex3f(-BOARD_SIDE,BOARD_SIDE,0.0f);
	glEnd();
	glPushMatrix();
	glTranslatef(0.0f, 0.0f, 0.001f);// THE UPEERLAYER FOR COLOR
	glColor3f(0.0f, 0.0f, 0.0f);// code for holes
	drawFillCircle(-BOARD_SIDE + HOLE_RADIUS, -BOARD_SIDE + HOLE_RADIUS , HOLE_RADIUS);
	drawFillCircle(BOARD_SIDE - HOLE_RADIUS, -BOARD_SIDE + HOLE_RADIUS , HOLE_RADIUS);
	drawFillCircle(BOARD_SIDE - HOLE_RADIUS, BOARD_SIDE - HOLE_RADIUS , HOLE_RADIUS);
	drawFillCircle(-BOARD_SIDE + HOLE_RADIUS, BOARD_SIDE -HOLE_RADIUS , HOLE_RADIUS);
	// DRAWING SIDE LINES
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(-BOARD_SIDE+LINE_HEIGHT, -BOARD_SIDE+LINE_SIDE +  LINE_WIDTH/2 , 0.0f);
	glVertex3f(-BOARD_SIDE+LINE_HEIGHT, BOARD_SIDE -LINE_SIDE -  LINE_WIDTH/2 , 0.0f);
	glVertex3f(BOARD_SIDE -LINE_HEIGHT, -BOARD_SIDE +LINE_SIDE +  LINE_WIDTH/2 , 0.0f);
	glVertex3f(BOARD_SIDE -LINE_HEIGHT, BOARD_SIDE -LINE_SIDE -  LINE_WIDTH/2 , 0.0f);
	glVertex3f(-BOARD_SIDE+LINE_SIDE +  LINE_WIDTH/2 , -BOARD_SIDE +LINE_HEIGHT , 0.0f);
	glVertex3f(BOARD_SIDE -LINE_SIDE -  LINE_WIDTH/2 , -BOARD_SIDE +LINE_HEIGHT , 0.0f);
	glVertex3f(-BOARD_SIDE+LINE_SIDE +  LINE_WIDTH/2 , BOARD_SIDE -LINE_HEIGHT , 0.0f);
	glVertex3f(BOARD_SIDE -LINE_SIDE -  LINE_WIDTH/2 , BOARD_SIDE -LINE_HEIGHT , 0.0f);
	glVertex3f(-BOARD_SIDE+LINE_HEIGHT+LINE_WIDTH, -BOARD_SIDE+LINE_SIDE +  LINE_WIDTH/2 , 0.0f);
	glVertex3f(-BOARD_SIDE+LINE_HEIGHT+LINE_WIDTH, BOARD_SIDE -LINE_SIDE -  LINE_WIDTH/2 , 0.0f);
	glVertex3f(BOARD_SIDE -LINE_HEIGHT-LINE_WIDTH, -BOARD_SIDE +LINE_SIDE +  LINE_WIDTH/2 , 0.0f);
	glVertex3f(BOARD_SIDE -LINE_HEIGHT-LINE_WIDTH, BOARD_SIDE -LINE_SIDE  -  LINE_WIDTH/2 , 0.0f);
	glVertex3f(-BOARD_SIDE+LINE_SIDE+  LINE_WIDTH/2 , -BOARD_SIDE +LINE_HEIGHT+LINE_WIDTH , 0.0f);
	glVertex3f(BOARD_SIDE -LINE_SIDE-  LINE_WIDTH/2 , -BOARD_SIDE +LINE_HEIGHT+LINE_WIDTH, 0.0f);
	glVertex3f(-BOARD_SIDE+LINE_SIDE+  LINE_WIDTH/2 , BOARD_SIDE -LINE_HEIGHT-LINE_WIDTH , 0.0f);
	glVertex3f(BOARD_SIDE -LINE_SIDE-  LINE_WIDTH/2 , BOARD_SIDE -LINE_HEIGHT-LINE_WIDTH , 0.0f);
	glEnd();
	//DRAWING CIRCLES AT THE END OF THE LINES
	drawLineCircle(BOARD_SIDE-LINE_HEIGHT - LINE_WIDTH/2 , BOARD_SIDE-LINE_SIDE - LINE_WIDTH/2 , LINE_WIDTH/2);
	drawLineCircle(-BOARD_SIDE+LINE_HEIGHT + LINE_WIDTH/2 , BOARD_SIDE-LINE_SIDE - LINE_WIDTH/2 , LINE_WIDTH/2);
	drawLineCircle(-BOARD_SIDE+LINE_HEIGHT + LINE_WIDTH/2 , -BOARD_SIDE+LINE_SIDE + LINE_WIDTH/2 , LINE_WIDTH/2);
	drawLineCircle(BOARD_SIDE-LINE_HEIGHT - LINE_WIDTH/2 , -BOARD_SIDE+LINE_SIDE + LINE_WIDTH/2 , LINE_WIDTH/2);
	drawLineCircle(BOARD_SIDE-LINE_SIDE - LINE_WIDTH/2 , BOARD_SIDE-LINE_HEIGHT - LINE_WIDTH/2 , LINE_WIDTH/2);
	drawLineCircle(BOARD_SIDE-LINE_SIDE - LINE_WIDTH/2 , -BOARD_SIDE+LINE_HEIGHT + LINE_WIDTH/2 , LINE_WIDTH/2);
	drawLineCircle(-BOARD_SIDE+LINE_SIDE + LINE_WIDTH/2 , -BOARD_SIDE+LINE_HEIGHT + LINE_WIDTH/2, LINE_WIDTH/2);
	drawLineCircle(-BOARD_SIDE+LINE_SIDE + LINE_WIDTH/2 , BOARD_SIDE-LINE_HEIGHT - LINE_WIDTH/2 , LINE_WIDTH/2);
	// circles in between the uppercircles
	glColor3f(1.0f, 0.0f, 0.0f);
	drawFillCircle(BOARD_SIDE-LINE_HEIGHT - LINE_WIDTH/2 , BOARD_SIDE-LINE_SIDE - LINE_WIDTH/2 , INNERCIRCLE_RADII);
	drawFillCircle(-BOARD_SIDE+LINE_HEIGHT + LINE_WIDTH/2 , BOARD_SIDE-LINE_SIDE - LINE_WIDTH/2 , INNERCIRCLE_RADII);
	drawFillCircle(-BOARD_SIDE+LINE_HEIGHT + LINE_WIDTH/2 , -BOARD_SIDE+LINE_SIDE + LINE_WIDTH/2 , INNERCIRCLE_RADII);
	drawFillCircle(BOARD_SIDE-LINE_HEIGHT - LINE_WIDTH/2 , -BOARD_SIDE+LINE_SIDE + LINE_WIDTH/2 , INNERCIRCLE_RADII);
	drawFillCircle(BOARD_SIDE-LINE_SIDE - LINE_WIDTH/2 , BOARD_SIDE-LINE_HEIGHT - LINE_WIDTH/2 , INNERCIRCLE_RADII);
	drawFillCircle(BOARD_SIDE-LINE_SIDE - LINE_WIDTH/2 , -BOARD_SIDE+LINE_HEIGHT + LINE_WIDTH/2 , INNERCIRCLE_RADII);
	drawFillCircle(-BOARD_SIDE+LINE_SIDE + LINE_WIDTH/2 , -BOARD_SIDE+LINE_HEIGHT + LINE_WIDTH/2, INNERCIRCLE_RADII);
	drawFillCircle(-BOARD_SIDE+LINE_SIDE + LINE_WIDTH/2 , BOARD_SIDE-LINE_HEIGHT - LINE_WIDTH/2 , INNERCIRCLE_RADII);
	// arrow lines
	glColor3f(0.0f, 0.0f, 0.0f);
	glBegin(GL_LINES);
	glVertex3f(BOARD_SIDE, BOARD_SIDE , 0.0f);
	glVertex3f(BOARD_SIDE-LINE_ARROW , BOARD_SIDE - LINE_ARROW ,0.0f);
	glVertex3f(-BOARD_SIDE, BOARD_SIDE , 0.0f);
	glVertex3f(-BOARD_SIDE+LINE_ARROW , BOARD_SIDE - LINE_ARROW ,0.0f);
	glVertex3f(-BOARD_SIDE, -BOARD_SIDE , 0.0f);
	glVertex3f(-BOARD_SIDE+LINE_ARROW , -BOARD_SIDE + LINE_ARROW ,0.0f);
	glVertex3f(BOARD_SIDE, -BOARD_SIDE , 0.0f);
	glVertex3f(BOARD_SIDE-LINE_ARROW , -BOARD_SIDE + LINE_ARROW ,0.0f);
	glEnd();
	// arrowcircles
	drawArc(BOARD_SIDE-LINE_ARROW+ARROWCIRCLERADIUS/1.414 , BOARD_SIDE-LINE_ARROW+ARROWCIRCLERADIUS/1.414, ARROWCIRCLERADIUS,  45 + 30 , 360 + 45 - 30);
	drawArc(-BOARD_SIDE+LINE_ARROW-ARROWCIRCLERADIUS/1.414 , BOARD_SIDE-LINE_ARROW+ARROWCIRCLERADIUS/1.414, ARROWCIRCLERADIUS, 90 + 45 + 30 , 90 + 360 + 45 - 30);
	drawArc(-BOARD_SIDE+LINE_ARROW-ARROWCIRCLERADIUS/1.414,-BOARD_SIDE+LINE_ARROW-ARROWCIRCLERADIUS/1.414, ARROWCIRCLERADIUS,  180 + 45 + 30 ,180 + 360 + 45 - 30);
	drawArc(BOARD_SIDE-LINE_ARROW+ARROWCIRCLERADIUS/1.414 ,-BOARD_SIDE+LINE_ARROW-ARROWCIRCLERADIUS/1.414, ARROWCIRCLERADIUS,  270 + 45 + 30 , 270 +360+45-30);
	// threecircleswhichmake the center
	drawLineCircle(0.0f, 0.0f , MID1CIRCLE_RADIUS);
	drawLineCircle(0.0f, 0.0f, MID2CIRCLE_RADIUS);
	glColor3f(1.0f , 0.0f, 0.0f);
	drawFillCircle(0.0f, 0.0f, MID3CIRCLE_RADIUS);
	//drawing the internal triangles
	glBegin(GL_TRIANGLES);
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(MID1CIRCLE_RADIUS,0.0f,0.0f);
	glVertex3f(MID2CIRCLE_RADIUS,SMALLSIDE,0.0f );
	glVertex3f(MID2CIRCLE_RADIUS,0.0f,0.0f );	
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(-MID1CIRCLE_RADIUS,0.0f,0.0f);
	glVertex3f(-MID2CIRCLE_RADIUS,0.0f,0.f );
	glVertex3f(-MID2CIRCLE_RADIUS,-SMALLSIDE,0.0f );
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f,MID1CIRCLE_RADIUS,0.0f);
	glVertex3f(0.0f,MID2CIRCLE_RADIUS,0.0f );
	glVertex3f(-SMALLSIDE,MID2CIRCLE_RADIUS,0.0f );
	glColor3f(0.0f, 0.0f, 0.0f);
	glVertex3f(0.0f,-MID1CIRCLE_RADIUS,0.0f);
	glVertex3f(SMALLSIDE,-MID2CIRCLE_RADIUS,0.0f );
	glVertex3f(0.0f,-MID2CIRCLE_RADIUS,0.0f );
	glEnd();
	
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f , 0.0f, 0.0f);
	glVertex3f(MID1CIRCLE_RADIUS,0.0f,0.0f);
	glVertex3f(MID2CIRCLE_RADIUS,0.0f,0.0f );
	glVertex3f(MID2CIRCLE_RADIUS,-SMALLSIDE,0.0f );
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f , 0.0f, 0.0f);
	glVertex3f(-MID1CIRCLE_RADIUS,0.0f,0.0f);
	glVertex3f(-MID2CIRCLE_RADIUS,SMALLSIDE,0.0f );
	glVertex3f(-MID2CIRCLE_RADIUS,0.0f,0.0f );
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f , 0.0f, 0.0f);
	glVertex3f(0.0f,-MID1CIRCLE_RADIUS,0.0f);
	glVertex3f(0.0f,-MID2CIRCLE_RADIUS,0.0f );
	glVertex3f(-SMALLSIDE,-MID2CIRCLE_RADIUS,0.0f );
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(0.0f , 0.0f, 0.0f);
	glVertex3f(0.0f,MID1CIRCLE_RADIUS,0.0f);
	glVertex3f(SMALLSIDE,MID2CIRCLE_RADIUS,0.0f );
	glVertex3f(0.0f,MID2CIRCLE_RADIUS,0.0f );	
	glEnd();

	glRotatef(45.0,0.0f,0.0f,1.0f);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(MID1CIRCLE_RADIUS,0.0f,0.0f);
	glVertex3f(MID2CIRCLE_RADIUS,SMALLSIDE,0.0f );
	glVertex3f(MID2CIRCLE_RADIUS,0.0f,0.0f );	
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(-MID1CIRCLE_RADIUS,0.0f,0.0f);
	glVertex3f(-MID2CIRCLE_RADIUS,0.0f,0.f );
	glVertex3f(-MID2CIRCLE_RADIUS,-SMALLSIDE,0.0f );
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f,MID1CIRCLE_RADIUS,0.0f);
	glVertex3f(0.0f,MID2CIRCLE_RADIUS,0.0f );
	glVertex3f(-SMALLSIDE,MID2CIRCLE_RADIUS,0.0f );
	glColor3f(1.0f, 0.0f, 0.0f);
	glVertex3f(0.0f,-MID1CIRCLE_RADIUS,0.0f);
	glVertex3f(SMALLSIDE,-MID2CIRCLE_RADIUS,0.0f );
	glVertex3f(0.0f,-MID2CIRCLE_RADIUS,0.0f );
	glEnd();
	
	glBegin(GL_LINE_LOOP);	
	glColor3f(1.0f , 0.0f, 0.0f);
	glVertex3f(MID1CIRCLE_RADIUS,0.0f,0.0f);
	glVertex3f(MID2CIRCLE_RADIUS,0.0f,0.0f );
	glVertex3f(MID2CIRCLE_RADIUS,-SMALLSIDE,0.0f );
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f , 0.0f, 0.0f);
	glVertex3f(-MID1CIRCLE_RADIUS,0.0f,0.0f);
	glVertex3f(-MID2CIRCLE_RADIUS,SMALLSIDE,0.0f );
	glVertex3f(-MID2CIRCLE_RADIUS,0.0f,0.0f );
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f , 0.0f, 0.0f);
	glVertex3f(0.0f,-MID1CIRCLE_RADIUS,0.0f);
	glVertex3f(0.0f,-MID2CIRCLE_RADIUS,0.0f );
	glVertex3f(-SMALLSIDE,-MID2CIRCLE_RADIUS,0.0f );
	glEnd();
	glBegin(GL_LINE_LOOP);
	glColor3f(1.0f , 0.0f, 0.0f);
	glVertex3f(0.0f,MID1CIRCLE_RADIUS,0.0f);
	glVertex3f(SMALLSIDE,MID2CIRCLE_RADIUS,0.0f );
	glVertex3f(0.0f,MID2CIRCLE_RADIUS,0.0f );
	
	glEnd();
	glRotatef(-45.0f,0.0f,0.0f,1.0f);
	
	glPopMatrix();	
}

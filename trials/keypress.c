// input output



void handleKeypress(unsigned char key, int x, int y)
{
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
		case 108:
			if(chance == 1 && coins[0].pos.x < BOARD_SIDE - LINE_SIDE-LINE_WIDTH/2)
			{
				coins[0].pos.x += 0.01f ;
				glutPostRedisplay();
			}
			break;
		case 106:
			if(chance== 1 && coins[0].pos.x > -BOARD_SIDE + LINE_SIDE+LINE_WIDTH/2)
			{
				coins[0].pos.x -= 0.01f ;
				glutPostRedisplay();
			}
			break;
		case 32:
			if(chance == 1)
			{
				coins[0].vel.x = -velocity*sin(ang*22.0f/7.0f/180.0f);
				coins[0].vel.y = velocity*cos(ang*22.0f/7.0f/180.0f);
				startqueue();
				chance =0;
			}
			break;
		case 104:
			zang = 180*playerno;
			xang = 0.0f;
			yang = 0.0f;
			break;
		case 27:
			gamepause = 1-gamepause;
			break;
	}
}





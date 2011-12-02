#include "opengltest4.c"
#include <string.h>

int main(int argc, char **argv)
{
	int i;
	int portno;
	if(argc == 1)
	{
		scanf("%d",&i);
		gametype = (char)i;
		scanf("%d",&i);
		scanf("%d", &portno);
	}
	else
	{
		i = atoi(argv[1]);
		portno =atoi(argv[2]);
		gametype = atoi(argv[3]);
		isAI[0] = atoi(argv[4]);
		if(argc > 5 && i == 0)
		{
			isAI[1] = atoi(argv[5]);
			if(gametype == 2)
			{
				isAI[2] = atoi(argv[6]);
				isAI[3] = atoi(argv[7]);
			}
		}
		
	
	}
	if( i==0)
	{
		createServer(portno);
		game(argc, argv , 0);
	}
	else
	{
		createClient(portno , "ubuntu");
		game(argc, argv , i);
	}
}



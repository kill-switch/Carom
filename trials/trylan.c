#include "opengltest4.c"


int main(int argc, char **argv)
{
	int i;
	scanf("%d",&i);
	int portno;
	scanf("%d", &portno);
	
	if( i==0)
	{
		createServer(portno);
		game(argc, argv , 0);
	}
	else
	{
		createClient(portno , "ubuntu");
		game(argc, argv , 1);
	}
}



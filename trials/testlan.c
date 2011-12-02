#include "langame.c"


int main()
{
	int i;
	scanf("%d",&i);
	int portno;
	scanf("%d", &portno);
	char c;
	char s[20];
	
	if( i==0)
	{
		createServer(portno);
	}
	else
	{
		createClient(portno , "ubuntu");
	}
	while(1)
	{
	c = getchar();
	
	if(c == '1')
	{
		printf("\ntransmiiting data\n");
		scanf("%s",s);
		sendData(s,sizeof(s),-1);
	}
	if(c=='2')
	{
		printf("\nrecieving data\n");
		recieveData(s,20);
		printf("this is the string %s",s);
		printf("hi");
	}
	}	
	
}

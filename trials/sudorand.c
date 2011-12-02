
// sudo random no generator 
#include<stdlib.h>



int getRand(int prob , int reset)
{
	static int prevprob;
	int randomno;
	if(reset == 1)
	{
		prevprob = 0;
	}
	
	prevprob = prevprob + getProb(prob);
	randno = random(100);
	


}

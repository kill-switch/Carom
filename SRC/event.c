// events
#include"event.h"
//working and ok
int isEqual(event a , event b)
{
	// did not introduce clock restrictions :/ check
		if(a.label==b.label)
			{
				if(a.ball1 == b.ball1 && a.ball2 == b.ball2)
				{
					if(a.time == b.time)
					{
						return 1;
					}
				}	
			}
	
	return 0;
}

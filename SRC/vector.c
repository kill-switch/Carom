// vectors
#include "vector.h"


vector multConstant(vector a, float constant)
{
	a.x = a.x*constant;
	a.y = a.y*constant;
	a.z = a.z*constant;
	return a;	
}


float dotProduct(vector a, vector b)
{
	return a.x*b.x + a.y*b.y + a.z*b.z;
}

float modValue(vector a)
{	
	
	return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

vector addVector(vector a, vector b)
{
	vector c;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
	return c;
}


vector subVector(vector a, vector b)
{
	vector c;
	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
	return c;
}


vector crossVector(vector a, vector b)
{
	vector c;
	c.x = a.y*b.z - a.z*b.y;
	c.y = b.x*a.z - a.x*b.z;
	c.z = a.x*b.y - a.y*b.x;
	return c;
}

float distanceLinePoint(vector vline,vector pointOnLine , vector targetPoint)
{	
	return (modValue(crossVector(subVector(targetPoint,pointOnLine),multConstant(vline,1/modValue(vline)))));
}

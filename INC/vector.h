#ifndef VECTOR_H
#define VECTOR_H
#include <math.h>
typedef struct 
{
	float x;
	float y;
	float z;
} vector;
vector multConstant(vector a, float constant);
float dotProduct(vector a, vector b);
float modValue(vector a);
vector addVector(vector a, vector b);
vector subVector(vector a, vector b);
vector crossVector(vector a, vector b);
float distanceLinePoint(vector vline,vector pointOnLine , vector targetPoint);
#endif

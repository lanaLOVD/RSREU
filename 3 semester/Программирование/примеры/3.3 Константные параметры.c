#include <stdio.h>
#include <math.h>


float cube(const float x)
{
	//x = 1; // [Error] assignment of read-only parameter 'x'
	return x * x * x;
}

int main() 
{
	float a = 5.0;
	float res = cube(a);
	
	printf("%f", res);
	
	return 0;
}



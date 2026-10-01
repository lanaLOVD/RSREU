#include <stdio.h>

// возвратить знак числа, с учётом нуля
int sgn(int num)
{
	return num > 0? 1 : (num < 0? -1 : 0);
}

int main() 
{
	printf("sgn: %d\n",sgn(-4)); // -1
	printf("sgn: %d\n",sgn(4)); // 1
	printf("sgn: %d\n",sgn(0)); // 0
		
	return 0;
}



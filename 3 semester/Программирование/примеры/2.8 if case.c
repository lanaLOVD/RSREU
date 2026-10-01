#include <stdio.h>


int main() 
{
	int i = 0;
	if(i) // ожидается значение, приводящееся к целочисленному
		printf("i!=0\n");
	else
		printf("i==0\n");
		
	i = 5;
	// если не указать break будут выполнены все операторы до следующего break
	// в case при наличии нескольких операторов составной оператор не требуется
	switch(i)
	{
		case 5:
			printf("5! ");
			//break;
		case 6:
			printf("6! ");
			//break;
		case 7:
			printf("7! ");
			//break;
		default:
			printf("default!");
	}
	printf("\n");
		
	return 0;
}


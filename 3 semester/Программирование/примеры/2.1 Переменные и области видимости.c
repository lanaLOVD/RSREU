#include <stdio.h>


// объ€вление переменной
int a;

// объ€вление и инициализаци€ нескольких переменных
int b = 2 , c = 3;

// объ€вление константы
const int numStudents = 30; 


/*****************************************************/


//глобальна€ переменна€
int i = 1; 

int getI() 
{
	return i;
}

int getLocalI() 
{
	//локальна€ переменна€ функции
	int i = 2; 
	
	return i;
}

int main() 
{
	int i = 3; //локальна€ переменна€
	printf("i = %d\n", i); // i = 3
	
	{
		int i = 4; //локальна€ переменна€
		printf("i = %d\n", i); // i = 4
	}
	
	printf("i = %d\n", getI()); // i = 1
	printf("i = %d\n", getLocalI()); // i = 2
	
	return 0;
}






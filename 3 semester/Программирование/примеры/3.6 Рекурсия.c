#include <stdio.h>
#include <math.h>


// расчёт факториала n! методом нисходящей рекурсии
int fact1(unsigned int n) 
{
	if(n == 0)
		return 1; // Терминальная ситуация
	else
		return n * fact1(n - 1); // рекурсивный вызов
}

// расчёт факториала n! методом восходящей рекурсии, w - рабочий параметр
int fact2(unsigned int n, unsigned int w) 
{
	if(n == 0)
		return w; // Терминальная ситуация
	else
		return fact2(n - 1, w * n); // рекурсивный вызов
}

int main() 
{
	system("chcp 1251");
	
	int n = 5;
	printf("Нисходящая рекурсия: %d! = %d\n", n, fact1(n));
	printf("Восходящая рекурсия: %d! = %d\n", n, fact2(n, 1));
	
	return 0;
}



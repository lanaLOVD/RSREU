#include <stdio.h>
#include <math.h>
#include <stdbool.h>

/* 
	Линейная рекурсия:
 	Нахождение НОД двух натуральных чисел по алгоритму Евклида:
 	если m является точным делителем n, то НОД = m, в противном 
	случае нужно брать функцию НОД от m и от остатка деления n на m
*/
int NOD(unsigned int n,unsigned int m)
{
	if(m > n)
		return NOD(m, n); // рекурсивная ветвь
	else
		if(m == 0)
			return n; // терминальная ветвь
		else
			return NOD(m, n % m); // рекурсивная ветвь
}

/* 
	Паралельная рекурсия:
   	Вычислить n-й член ряда Фибоначчи F(0) = 0, F(1) = 1, F(N) = F(N-1) + F(N-2)
*/
int fibo(unsigned int n)
{
	if(n == 0)
		return 0; // терминальная ветвь
	else
		if(n == 1)
			return 1; // терминальная ветвь
		else
			return fibo(n - 1) + fibo(n - 2); // рекурсивная ветвь
		
}

/*
	Взаимная рекурсия:
	проверить является ли число чётным или нечётным (пример искусственный и неэффективный)
*/
bool isOdd(unsigned int n);
bool isEven(unsigned int n) 
{
  if (n == 0) 
	return true;
  else 
	return isOdd(n - 1); // взаимный рекурсивный вызов
}

bool isOdd(unsigned int n) 
{
  if(n == 0) 
	return false;
  else 
	return isEven(n - 1); // взаимный рекурсивный вызов
}


/*
	Рекурсия более высокого порядка:
	рассчитать функцию Аккермана для m и n
	A(m, n) = n+1			при m = 0;
	A(m, n) = A(m-1, 1)		при n = 0;
	A(m, n) = A(m-1, A(m, n-1))	в остальных случаях.
*/
int ackerman(unsigned int m, unsigned int n)
{
	if(m == 0)
		return n + 1;
	else
		if(n == 0)
			return ackerman(m - 1, 1);
		else
			return ackerman(m - 1, ackerman(m, n - 1));
}

int main() 
{
	system("chcp 1251");
	
	int i = 42, j = 12;
	printf("Наибольший общий делитель для %d и %d: %d\n", i, j, NOD(i, j));
	
	int f = 15;
	printf("Число Фиббоначчи для %d-го члена: %d\n",f, fibo(f));
	
	int d = 13;
	printf("Число %d чётное: %s\n", d, isEven(d)? "да" : "нет");
	printf("Число %d нечётное: %s\n", d, isOdd(d)? "да" : "нет");
	
	int n = 3, m = 4;
	printf("Функция Аккермана для %d и %d : %d", n, m, ackerman(n,m));

	return 0;
}



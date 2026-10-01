#include <stdlib.h>
#include <stdio.h>
#include <mem.h>

int* createDynArray(int size);
void printDynArray(const int* array, int size);

#define ARR_SIZE 10

int main() 
{
	//создаём два динамических массива из 10 элементов
	int *a = createDynArray(ARR_SIZE), *b = createDynArray(ARR_SIZE);
	
	if(!a || !b) printf("Error!"), exit(1);
	
	//заполняем массивы
	int i;
	for(i = 0; i < ARR_SIZE; i++) 
		a[i] = b[ARR_SIZE - 1 - i] = i * i;
	
	//выводим массивы
	printDynArray(a, ARR_SIZE);
	printDynArray(b, ARR_SIZE);	
	printf("\n");
	
	const int arrSizeHalf = ARR_SIZE / 2;
	//копируем последние 5 элементов из массива a в первые 5 элементов массива b
	memcpy(b, a + arrSizeHalf, arrSizeHalf * sizeof(int));
	
	//зануляем первые 5 элементов из массива a и последние 5 элементов массива b
	memset(a, 0, arrSizeHalf * sizeof(int));	
	memset(b + arrSizeHalf, 0, arrSizeHalf * sizeof(int));
	
	//выводим массивы
	printDynArray(a,ARR_SIZE);
	printDynArray(b,ARR_SIZE);	
	
	//не забываем освободить память
	free(a); 
	free(b); 
	a = b = NULL;
	
	return 0;
}



//функция возвращает указатель на динамический массив размера size элементов
int* createDynArray(int size)
{	
	//проверка на допустимый размер
	if(size < 1) return NULL;
	
	//выделяем память под size элементов
	int* p = (int*)calloc(size, sizeof(int));
	
	//если память не выделилась - возвращаем нулевой указатель
	if(!p) return NULL;
	
	//возвращаем указатель на первый элемент массива
	return p;
}

//вывод массива на экран
void printDynArray(const int* array, int size)
{
	int i;
	for(i = 0; i < size; ++i)
		printf("\t%d", array[i]);	
	printf("\n");
}

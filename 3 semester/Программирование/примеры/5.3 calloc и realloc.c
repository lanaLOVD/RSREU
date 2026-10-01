#include <stdlib.h>
#include <stdio.h>

//функция возвращает указатель на динамический массив размера size элементов
float* createDynArray(int size)
{	
	//проверка на допустимый размер
	if(size < 1) return NULL;
	
	//выделяем память под size элементов
	float* p = (float*)calloc(size, sizeof(float));
	
	//если память не выделилась - возвращаем нулевой указатель
	if(!p) return NULL;
	
	//возвращаем указатель на первый элемент массива
	return p;
}

//функция изменения размера массива до newsize элементов
float* resizeDynArray(float* array, int newsize)
{
	//проверка на допустимый размер
	if(newsize < 1) return NULL;
		
	//выделение новой памяти
	float* p = (float*)realloc(array, newsize * sizeof(float));
	
	//если не удалось - возвращаем NULL
	if(!p) return NULL;
	
	//возвращаем указатель на первый элемент массива, т.к.
	//адрес мог измениться!
	return p;
}

//вывод массива на экран
void printDynArray(const float* array, int size)
{
	int i;
	for(i = 0; i < size; ++i)
		printf("%f ", array[i]);	
	printf("\n");
}

int main() 
{
	//создаём динамический массив из 5 элементов
	float* array = createDynArray(5);
	if(!array) printf("Error!"), exit(1);
	
	//выводим элементы массива
	printDynArray(array, 5);
		
	//увеличиваем размер динамического массива
	array = resizeDynArray(array, 15);
	if(!array) printf("Error!"), exit(1);
	
	//выводим новые элементы массива
	printDynArray(array, 15); //cодержимое добавленной части памяти не определено, 
							 //поэтому может выводиться мусор
		
	free(array); //не забываем освободить память
	array = NULL;
	
	return 0;
}


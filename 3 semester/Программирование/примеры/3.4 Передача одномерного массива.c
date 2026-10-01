#include <stdio.h>
#include <math.h>

// массивы всегда передаются по адресу, поэтому их элементы
// могут быть изменены внутри функции
void doubleElems(int array[], int len) 
{
	int i;
	
	for(i = 0; i < len; ++i)
		array[i] *= array[i];
}

// если предполагается только чтение элементов, массив
// следует передавать как константный параметр
float getAvgValue(const int array[], int len) 
{
	int i, sum = 0;
	
	for(i = 0; i < len; ++i)
		sum += array[i];
		
	return (float) sum / len;
}

// если константный параметр не будет указан, это будет
// вводить в заблуждение использующих данную функцию.
void print(const int array[], int len) 
{
	int i;
	
	for(i = 0; i < len; ++i)
		printf("%d ", array[i]);
		
	printf("\n");
}

int main() 
{
	system("chcp 1251");
	
	int array[]={1,5,-4,6,9};
	
	print(array, 5);
	doubleElems(array, 5); // массив модифицируется в данной функции
	print(array, 5);
	printf("Среднее значение: %f", getAvgValue(array,5)); // 31.7999

	return 0;
}



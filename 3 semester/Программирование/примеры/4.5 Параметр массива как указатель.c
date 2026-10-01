#include <stdio.h>

void print(const int* array,int len) //аналогично const int array[]
{
	int i;
	for(i=0; i<len;i++)
		printf("%d ",*(array+i)); //аналогично array[i]
	printf("\n");
}

void inline swap(int* a, int* b) //поменять значения местами
{
	int temp= *a;
	*a = *b;
	*b = temp;
}

void reverse(int* array, int len) //аналогично int array[]
{
  int start = 0, end = len - 1;
  
  while (start < end)  
	swap((array + start++), (array + end--));
}


// заменить значение элемента на 1 если сумма индексов чётная,
// и на -1 - если нечётная
float calcOddEven(int* array, unsigned int rows, unsigned int cols)
{
	int i,j;
	
	for(i=0;i<rows;i++)
		for(j=0;j<cols;j++)
		{
			int* elem = (array + i * cols + j); // array2d[imax][jmax] => array1d[i * jmax + j]
			*elem = (i + j) % 2 == 0 ? 1 : -1;
		}
}

int main() 
{
	int a[] = {1, 2, 3, 4, 5};
	
	reverse(a, 5); // имя 1d массива - указатель на его первый элемент
	print(a, 5); // 5, 4, 3, 2, 1
	
	
	#define ROWS 3
	#define COLS 2
	int mat[ROWS][COLS];
							
	calcOddEven((int*)mat, ROWS, COLS);  //при явном приведенни типа не будет Warning

	print((int*)mat, ROWS * COLS); // при сведении 2d массива можно использовать функцию для 1d массива

	/* mat =  1 -1 
			 -1  1 
			  1 -1
	*/
	
	/*  Важно помнить что в 1d массиве его имя указывает на первый элемент int*
		в то время как в 2d массиве его имя указывает на 1d массив int(*)[]
	*/
	
	return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5
 
int main() 
{
	int i, j;
	
	//создаём массив указателей размером SIZE
    int** A = (int**) malloc(SIZE * sizeof(int*));
 
 	//для каждого элемента-указателя создаём свой массив
 	//размер которого увеличивается с 1 до SIZE
    for (i = 0; i < SIZE; ++i)
        A[i] = (int*) malloc((i + 1) * sizeof(int));
 
 	//заполняем двумерный треугольный массив
 	int c = 1;
    for (i = 0; i < SIZE; ++i) 
        for (j = 0; j < i + 1; ++j) 
            A[i][j] = c++;
        
    
 	//выводим двумерный треугольный массив
    for (i = 0; i < SIZE; ++i) 
    {
        for (j = 0; j < i + 1; ++j) 
            printf("\t%d", A[i][j]);
        printf("\n");
    }
    /*
        1
        2       3
        4       5       6
        7       8       9       10
        11      12      13      14      15
    */

	//очищаем сначала под-массивы
    for (i = 0; i < SIZE; ++i)  
		free(A[i]);
    
    //потом очищаем основной массив
	free(A); 
	A = NULL;
     
	return 0;
}

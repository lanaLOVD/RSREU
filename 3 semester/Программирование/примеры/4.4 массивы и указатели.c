#include <stdio.h>

void sum(int num, const float array1[], const float array2[], float arrayRes[]);
void print(int rows, int cols, const float array[][cols]);

main()
{
	// ќдномерные массивы:
	// ¬ывести все чЄтные элементы в обратном пор€дке
	
	int a[]={1, 2, 3, 4, 5};

	// размер массива в байтах sizeof(a) 
	// расчитываетс€ на этапе компил€ции
	unsigned int count = sizeof(a) / sizeof(a[0]); 

	// ”казатель на последний элемент
	int *a_end = a + count - 1; 
	
	//выводим все чЄтные элементы в обратном пор€дке
	int *ptr;
	for (ptr = a_end; ptr >= a; ptr--) 
	    if(*ptr % 2 == 0) 
			printf("%d ", *ptr); // 4 2
	printf("\n");		
			
			
			
	// ƒвумерные массивы:
	// сложить две матрицы
	#define ROWS 3
	#define COLS 2
	int i,j;
	float mat1[ROWS][COLS] = {1, 2, 3, 4, 5, 6};
	float mat2[ROWS][COLS] = {7, 8, 9, 10, 11, 12};
	float mat3[ROWS][COLS];
	
	//  mat1: 1.0        2.0	mat2: 7.0        8.0
	//        3.0        4.0  	      9.0        10.0
	//        5.0        6.0  	      11.0       12.0
	
	// в случае с двумерным массивом его им€ также указывает на его первый
	// элемент, но в данном случае его элементы €вл€ютс€ одномерными массивами
	// (т.к. двумерный массив это одномерный массив из элементов €вл€ющихс€ одномерными массивами)
	
	for(j = 0; j < COLS; j++)
		printf("%f ",(*(mat1 + 1))[j]); // вывести 2-ю строку матрицы mat1
	printf("\n");
	for(j = 0; j < COLS; j++)
		printf("%f ",*(*(mat1 + 2) + j)); // вывести 3-ю строку матрицы mat1
	printf("\n");
	
	
	// передаЄм в функцию одномерные массивы, т.е. матрицу по-строчно
	for(i=0; i<ROWS;i++)
			sum(COLS, *(mat1 + i), *(mat2 + i), *(mat3 + i)); 
			
	printf("mat3:\n");		
	print(ROWS, COLS, mat3);
	
	//  mat3: 8.0        10.0
	//        12.0       14.0
	//        16.0       18.0	
	
	// способ со "сведением" массива (array flatten) из двумерного в одномерный
	// "сведение" (flatten) массива - это уменьшение размерности массива
	float* p1 = (float*) mat1; //€вно указываем на элемент mat1[0][0]
	float* p2 = (float*) mat2; //€вно указываем на элемент mat2[0][0]
	float* p3 = (float*) mat3; //€вно указываем на элемент mat3[0][0]
	unsigned int size = ROWS * COLS; //кол-во элементов в матрицах
	
	
	for(i = 0; i < size; i++)
		*p3++ = *p1++ + *p2++; //прибавл€ем элементы и сдвигаем указатели


	printf("mat3:\n");
	print(ROWS,COLS,mat3);
	
	//  mat3: 8.0        10.0
	//        12.0       14.0
	//        16.0       18.0	

}

void sum(int num, const float array1[], const float array2[], float arrayRes[])
{
	int i;
	for(i = 0; i < num; ++i)
		arrayRes[i] = array1[i] + array2[i];
}

void print(int rows, int cols, const float array[][cols])
{
	int i,j;

	for(i=0; i<rows;i++)
	{
		for(j=0; j<cols;j++)
			printf("\t%f",array[i][j]);
		printf("\n");
	}
}

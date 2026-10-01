#include <stdio.h>
#include <math.h>
#include <stdbool.h>

/*
	«адача: сформировать двумерный массив символов и вывести его на экран. 
	√раничные символы должны быть СxТ, остальные если произведение индексов 
	чЄтное Ц С Т, нечЄтное С-Т.
*/

//диапазон размеров пр€моугольника
const int rangeLow = 2;
const int rangeHigh = 50;


//попадает ли val в диапазон [min...max]
bool inline inRange(int val, int min, int max)
{
	return val >= min && val <= max;
}

//об€зательно указать заголовки функций, если вызов предшествует объ€влению
//имена параметров можно не указывать
void fillArray(char [][50], int, int);
void printArray(const char [][50], int, int);

int main() 
{
	char arr[50][50];
	int sizeX,sizeY;
	
	//устанавливаем кодировку дл€ русских символов
//	SetConsoleCP(1251); 
//	SetConsoleOutputCP(1251);
    system("chcp 1251");
	
	//ввод и проверка данных
	do
	{
		printf("¬ведите ширину и высоту пр€моугольника в диапазоне [%d...%d]:\n", rangeLow, rangeHigh);
		scanf("%d%d", &sizeX,&sizeY);
		
		if(inRange(sizeX,rangeLow,rangeHigh) && inRange(sizeY,rangeLow,rangeHigh))
		{
			break;
		}
		else
			printf("ќшибка! введите ещЄ раз!\n"); 
	}while(true);
	
	//заполн€ем массив символов
	fillArray(arr, sizeX, sizeY);
	
	//выводим пр€моугольник
	printArray(arr, sizeX, sizeY);
		
	return 0;
}


//попадают ли x,y на границу пр€моугольника заданного размера
bool inline isBorder(int x, int y, int sizeX, int sizeY)
{
	return x==0 || x==sizeX || y==0 || y==sizeY;
}

//чЄтное ли число
bool inline isEven(int val)
{
	return val % 2 == 0;
}

// заполн€ем двумерный массив в соотвествии с задачей. ¬торую размерность следует указать €вно
void fillArray(char arr[][50], int sizeX, int sizeY)
{
	int i,j;
	
	for(j = 0; j < sizeY; j++)
		for(i = 0; i < sizeX; i++)
			arr[i][j] = isBorder(i, j, sizeX -1 , sizeY - 1) ? 'x' : (isEven(i * j) ? ' ' : '-');			
}

// выводим двумерный массив на экран. Ќе забываем const!
void printArray(const char arr[][50], int sizeX, int sizeY)
{
	int i,j;

	for(j = 0; j < sizeY; j++)
	{
		for(i = 0; i < sizeX; i++)
			printf("%c", arr[i][j]);
		printf("\n");
	}
}

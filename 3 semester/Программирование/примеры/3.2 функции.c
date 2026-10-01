#include <stdio.h>
#include <math.h>

// здесь требуется предварительное объявление, т.к. distance объявлен
// ниже его первого вызова
float distance(float x1, float y1, float x2, float y2);

// тип void задаёт функцию которая не возвращает значения (процедура)
// и\или не принимает никаких аргументов
void printBeginTitle(void)
{
	printf("--------------------------\n");
	printf("Пример по функциям\n");
	printf("--------------------------\n");	
}

printEndTitle() // void в параметрах можно опустить
{
	printf("--------------------------\n");
	printf("Конец примера по функциям\n");
	printf("--------------------------\n");	
	
	return 0; // по-умолчанию тип возвращаемого значения - int
}

int main() 
{
	system("chcp 1251");
	
	printBeginTitle();
	
	// вызов distance предшествует её объявлению - значит требуется предварительное объявление!
	printf("Расстояние: %f\n", distance(1.0f, 0.0f, 5.0f, 0.0f)); //  4.0
	
	printEndTitle();
	
	return 0;
}

// inline подсказывает компилятору, что данную функцию следует
// встроить в каждое место вызова, экономя время на её вызове
inline float sub(float a, float b)
{
	return a - b;
}

inline float distance(float x1, float y1, float x2, float y2)
{
	return sqrt(pow(sub(x1, x2), 2.0f) + pow(sub(y1, y2), 2.0f));
}

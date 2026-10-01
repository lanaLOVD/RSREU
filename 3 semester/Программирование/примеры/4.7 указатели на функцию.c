#include <stdio.h>


void doubleInt(void* x);
void doubleFloat(void* x);
void map(void* arr, int num, size_t size, void (*fun)(void *));


float doSum(float a, float b) 
{
    return a + b;
}

float doSub(float a, float b) 
{
    return a - b;
}

int main() 
{
	//переменна€ func типа указатель на функцию вида float (float, float)
	float (*func)(float, float) = NULL; 
	
	//ѕрисваиваем указателю значение - адрес функции
    //Ёто похоже на работу с массивом: операцию вз€ти€ адреса использовать не нужно
	func = doSum;
	printf("%f \n", func(1.5f, 0.2f)); //1.7
	func = doSub;
	printf("%f \n", func(1.5f, 0.2f)); //1.3
	
	
	// -----------------------------------------------------
	
	/*	
		“ип void* может пригодитьс€, когда мы хотим передавать указатель
		на функцию, способную работать с разными типами данных в качестве параметра
	*/
	
    int a[] = {1, 2, 3, 4};
    float b[] = {1.1f, 2.2f, 3.3f, 4.4f};
    
    map(a,4,sizeof(int),doubleInt); //удваиваем элементы массива a
    map(b,4,sizeof(float),doubleFloat); //удваиваем элементы массива b
    
	//выводим элементы массивов
    int i;
    for(i = 0; i < 4; ++i)
    	printf("%d %f \n",a[i],b[i]);
 
	// 2 2.2
	// 4 4.4
	// 6 6.6
	// 8 8.8
}


//функц€ удвоени€ int переменных
void doubleInt(void* x) 
{
	*((int*) x) *= 2;
}

//функц€ удвоени€ float переменных
void doubleFloat(void* x) 
{
    *((float*) x) *= 2.0f;
}

//‘ункци€ принимает массив, его размер, размер одного элемента и указатель на функцию,
//котора€ далее примен€етс€ ко всем элементам массива
void map(void* arr, int num, size_t size, void (*fun)(void *)) 
{
    int i;
    char* p = arr; // приводим указатель к типу char* (т.к. смещение задано в байтах)
    for (i = 0; i < num; ++i) 
		//вызываем функцию и передаЄм адрес следующего элемента массива
		fun(p + i * size); 
}

#include <stdio.h>

//получать при каждом вызове уникальный номер
//каждый раз на единицу больше предыдущего
unsigned int getUniqID()
{
	//статическая переменная хранит свое значение
	//между вызовами функции
	static unsigned int id = 1;
	return id++;
}

int main() 
{
	printf("%d\n", getUniqID()); // 1
	printf("%d\n", getUniqID()); // 2
	printf("%d\n", getUniqID()); // 3
	
	return 0;
}





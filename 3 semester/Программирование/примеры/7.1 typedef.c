#include <stdio.h>

int main(int argc, char** argv) 
{
	
	//объ€вл€ем новое им€ типа
	typedef unsigned int UInt;
	
	//теперь его можно использовать как любой другой тип
	UInt a = 5 + 2;
	printf("%d", a); // 7
	
	//можно определить им€ типа дл€ указател€
	typedef int* IntPtr;
	IntPtr ptr; //и создавать указатели данного типа
	
	//можно упростить объ€вление типа дл€ указателей на функции
	typedef float (*MathFunc)(float);
	MathFunc funcPtr; //указатель на функцию
	
	//или определить им€ типа дл€ массива
	typedef int IntArr[6];
	IntArr arr = {1,2,3,4,5,6};

	
	return 0;
}

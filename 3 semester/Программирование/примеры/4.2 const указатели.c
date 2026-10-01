#include <stdio.h>

// все возможные варианты параметров - указателей:
/*
void func(int* ptr, const int* ptrToConst, int* const constPtr, const int* const constPtrToConst)
{
    *ptr = 0; //OK: меняет данные по указателю.
    ptr = NULL; //OK: меняет указатель.
    
    *ptrToConst = 0; //Ошибка! Нельзя менять данные по указателю.
    ptrToConst = NULL; //OK: меняет указатель.
    
    *constPtr = 0; //OK: меняет данные по указателю.
    constPtr  = NULL; //Ошибка! Нельзя менять указатель.
    
    *constPtrToConst = 0; //Ошибка! Нельзя менять данные по указателю.
    constPtrToConst  = NULL; //Ошибка! Нельзя менять указатель.
}
//*/

int main()
{
	//спецификатор const можно обойти через приведение к соотвествующему типу указателя без const:
	
	const int a = 3;
	
	// ...
	
	int *ptr1 = &a; // Warning!
	int *ptr2 = (int*) &a; // No warning!
	
	// ...
	
	*ptr1 += 2;
	*ptr2 *= 10;
	
	printf("%d", *ptr2); // 50
	
	return 0;
}

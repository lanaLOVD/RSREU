#include <stdio.h>

 

  
int main()
{
	/*
		Пример того, как с помощью объединения можно использовать в разное
		время одну и ту же область памяти и как int и как float
	*/
	
	union 
	{
		int i;
		float f;
	} myUnion; //объявление переменной типа анонимное объединение
	
	myUnion.i = 5;
	printf("%d\n",myUnion.i); // 5
	
	myUnion.f = -0.5f;
	printf("%f\n",myUnion.f); // -0.5
	
	
	printf("%d\n",myUnion.i); // -1090519040 (ошибка!)
  
  
	// -------------------------------

	/*
		В данном примере показывается, как с помощью объединения
		удобно обращаться к байтам переменной типа int через
		массив char[4]
	*/
	
	union typeInt //объявление объединения (можно использовать typedef как и со struct)
	{
	  int i;
	  unsigned char b[4];
	};
	
	union typeInt value; 
  
	
	printf("N = ");
	scanf("%d", &value.i);
	
	//выводим int по-байтно в 16-ричной форме
	printf("%d = %x %x %x %x\n", value.i, value.b[3], value.b[2], value.b[1], value.b[0]);
  
  return 0;
}

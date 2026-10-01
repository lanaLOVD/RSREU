#include <stdio.h>
#include <math.h>
#include <string.h>

#define integer int
#define DSC_INPUT "Введите угол в радианах:"
#define PI 3.14159265
//макроопределение с параметрами (макрос)
#define SIN(x) sin(x * PI / 180.0f)

//объявляем переменную заданного типа, с заданным именем типа var_*** 
//и начальным значением
#define DECLARE_AND_SET(type, varname, value) type var_##varname = value;

#define SUM(A,B) (A+ \
				  B)
				  
				  
#define SUM_BAD(A,B) A+B
#define SUM_GOOD(A,B) (A+B)		
		  
#define STRINGIZE(x) #x

int main()
{	
	system("chcp 1251"); 
	
	//через include можно даже вставлять часть кода в функции 
	#include "6.5 part.c"
	
	integer c;
	puts(DSC_INPUT);
	scanf("%d", &c);
	printf("sin(%d) = %f\n", c, SIN(c));
	
	
	DECLARE_AND_SET(integer, num1, 4 * 2);
	printf("%d\n", var_num1); //8
	
	
	// однако при использовании макроопределений следует соблюдать осторожность!
	int a = 3, b = 5, r = 2;
	
	printf("%d\n", SUM_BAD(a,b) * r); // 13!
	printf("%d\n", SUM_GOOD(a,b) * r); // 16
	
	
	const char* str = STRINGIZE(hello); 
	puts(str); // str теперь содержит строку "hello"
  
	
	return 0;
}

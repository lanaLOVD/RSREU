#include <stdio.h>

int main(int argc,char** argv)
{
	system("chcp 1251"); 
	
	printf("Полный путь: %s\n", argv[0]);
	
	if(argc > 1)
	{
		int i;
		for(i = 1; i < argc; ++i)
			printf("аргумент №%d = \"%s\"\n", i, argv[i]);
	}
	else
		puts("Нет аргументов");
		
	return 0;
}

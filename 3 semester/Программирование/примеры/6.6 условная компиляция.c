#include <stdio.h>


#define DEBUG
#define VERSION 4

int main()
{
	system("chcp 1251"); 

	#if VERSION < 3
		puts("Обнаружена очень старая версия программы! Установите последнюю версию!\n");
		exit(1);
	#elif VERSION < 5
		puts("Доступны новые обновления, рекомендуется обновить программу...\n");
	#endif
	
	// отменяем объявление DEBUG
	//#undef DEBUG
	
	#ifdef DEBUG
		puts("Отладочная версия программы.\n");
	#else
		puts("Релизная версия программы.\n");
	#endif

  return 0;
}

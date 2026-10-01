#include <stdio.h>
#include <stdbool.h>

int main(int argc, char** argv) 
{
	
	char flags = 0; // 00000000
	
	const char flag1 = 1; // 00000001
	const char flag2 = 2; // 00000010
	const char flag3 = 4; // 00000100
	
	//установка флага
	flags = flags | flag1; 	// 00000001
	flags |= flag3; 		// 00000101
	
	//проверка флага
	bool isSet = flags & flag1; // !=0, true
	isSet = flags & flag2; // ==0, false
	
	//снять флаг
	flags &= ~flag1; // 00000100
	
	//инверсия (переключение) флагов
	flags = flags ^ flag2; // 00000110
	flags ^= flag2; // 00000100
	
	//очистить все флаги
	flags = 0; // 00000000
	
	// -------------------
	
	// работа с масками:
	
	//установка флагов по маске
	char mask = flag1 | flag2;  	// 00000011
	flags |= flag3; 				// 00000100
	flags |= mask; 					// 00000111
	
	//проверка флагов по маске
	isSet = flags & mask == mask; // true, flag1 и flag2 установлены

	//снятие флагов по маске
	flags = flags & ~mask; //сняли флаги flag1 и flag2, 00000100
	
	//инверсия (переключение) флагов на противоположные по маске
	mask = flag2 | flag3; // 00000110
	flags = 0xff; //включаем все флаги, 11111111
	flags = flags ^ mask; //переключили флаги по маске: 11111001  
	flags = flags ^ mask; //переключили флаги по маске: 11111111  
	
	// -------------------
	
	// Флаги удобно использовать вместе с перечислениями:
	
	//Перечисление прав пользователя
	enum Rights
	{
		NONE = 0,
		READ = 1,
		WRITE = 2,
		EXECUTE = 4
	};
	
	enum Rights userRights = READ | EXECUTE; //установка прав на чтение и исполнение
	
	if(userRights & EXECUTE)
		printf("user can execute!");  
		
	return 0;
	
}

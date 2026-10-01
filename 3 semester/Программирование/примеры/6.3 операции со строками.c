#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>



int main() 
{
	system("chcp 1251"); 
	
	char* name = (char*) malloc(10); // выделяем память под 10 символов
	puts("Введите имя:");
	scanf("%9s", name); // %9s ограничит ввод первыми 9 символами, 10 будет '\0'
	printf("Ваше имя %s\n", name);
	free(name);
	name = NULL;
	
	// после scanf и перед считыванием из потока ввода через fgets
	// лучше сбросить буфер stdin, иначе туда может попасть символ '\n'
	// и ввод через fgets будет пропущен
	fflush(stdin);
	
	// -----------------------------------------------------------------
	// Пример замены в тексте подстроки на другую подстроку
	// -----------------------------------------------------------------
	char s1[20], s2[20], text[2000]; 

	puts("Введите текст:");
	fgets(text, 100, stdin); //получаем текст

	if(strlen(text) < 5) 
		puts("Введите текст больше 5 символов"), exit(1);
	
	puts("Введите две последовательности символов для замены \"чего\" на \"что\" через пробел:");
	scanf("%19s %19s", s1, s2); //получаем строки замены
	

	int s1Len = strlen(s1), 
		s2Len = strlen(s2), 
		textLen = strlen(text);
	
	if(!s1Len || !s2Len) 
		puts("введите хотя бы по 1 символу замены"), exit(1);
	
	int i=0;
	int offset = s2Len - s1Len;
	while(i != strlen(text)) //в цикле проходим все символы text
	{
		if(strncmp(text + i, s1, s1Len) == 0) //и если нашли совпадение
		{
			if(offset != 0) // строки замены не совпадают по размеру
			{
				int from = offset > 0 ? strlen(text) : (i + s2Len);
				int to = offset > 0 ? i : (strlen(text) + 1);
				int mod = offset > 0 ? -1 : 1;
				
				int j;
				for(j = from; j != to; j += mod)
					text[j + offset] = text[j];
			}

			memcpy(text + i, s2, s2Len * sizeof(char)); //копируем подстроку в строку
			i += s2Len;

			continue;
		}
		i++;
	}
	
	puts(text);

	return 0;
}

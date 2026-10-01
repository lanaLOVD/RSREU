#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
 
const char* fileName = "8.2 test.txt";
const char* ErrorOpen = "Невозможно открыть файл.";
const char* ErrorClose = "Ошибка закрытия файла.";

int main()
{
	system("chcp 1251");
	
	//открываем файл на запись
	FILE *file = fopen(fileName, "w"); 
	if (!file) 
		puts(ErrorOpen), exit(1);
	
	fputs("Первая строка\nВторая строка", file); //записываем две строки
	fputs(" и ещё далее\n", file); //дописываем во вторую строку
	
	//записываем форматированную строку
	fprintf(file, "Формат: [%d] [%f]\nНовая строка!", 42, 1.32f);
	
	//закрываем файл
	if(fclose(file)) 
		puts(ErrorClose), exit(1);
	
	//-------------------------------------------
	
	//открываем файл на добавление
	if (!(file = fopen(fileName, "a"))) 
		puts(ErrorOpen), exit(1);
	
	fputc('\n', file);  //переход на новую строку
	fputs("Последняя строка", file); //записываем строку
	fputc('!', file); //дописываем последний символ
	
	//закрываем файл
	if(fclose(file)) 
		puts(ErrorClose), exit(1);	
	
	//-------------------------------------------
	
	//открываем файл на чтение
	if (!(file = fopen(fileName, "r"))) 
		puts(ErrorOpen), exit(1);
	
	char line1[50], line2[50], str[20];
	int intVar;
	float floatVar;
	
	//считываем данные первых 3х строк
	fgets(line1, 50, file);
	fgets(line2, 50, file);
	fscanf(file,"%19s [%d] [%f]",str, &intVar, &floatVar);
	
	//удаляем переносы в конце строк (т.к. они считываются с \n)
	line1[strlen(line1) - 1] = line2[strlen(line2) - 1] = '\0';
	
	//закрываем файл
	if(fclose(file)) 
		puts(ErrorClose), exit(1);	
	
	printf("Содержимое файла:\n%s\n%s\n%f\n%d\n%s\n",
					line1, line2, floatVar, intVar, str);
	
	
	return 0;
}

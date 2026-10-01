#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <locale.h>
 
const char* fileName = "8.3 test.bin";
const char* ErrorOpen = "Невозможно открыть файл.";
const char* ErrorClose = "Ошибка закрытия файла.";

int main()
{
	system("chcp 1251");
	
	typedef struct
	{
		char surname[30];
		unsigned char age;
		unsigned int salary;
		float tax;
	} Person;
	
	Person persons[4]={
						{"иванов", 38, 34000, 0.13},
						{"петров", 27, 27000, 0.13},
						{"иванов", 55, 55000, 0.06},
						{"сидоров", 40, 32000, 0.0},
					  };
	
	
	
	//открываем файл на запись
	FILE *file = fopen(fileName, "wb"); 
	if (!file) 
		puts(ErrorOpen), exit(1);
	
	//записываем массив в файл 
	fwrite(persons, sizeof(Person), 4, file);
	
	//закрываем файл
	if(fclose(file)) 
		puts(ErrorClose), exit(1);	
	
	
	//----------------------------------
	
	//открываем файл на чтение
	if (!(file=fopen(fileName, "rb"))) 
		puts(ErrorOpen), exit(1);
	
	puts("Укажите фамилию человека, которую необходимо найти:");
	char findName[30];
	scanf("%29s",findName);
	
	//проверка введеной фамилии
	int i, len = strlen(findName);
	if(len<2) puts("Введите фамилию!"), exit(1);
	
	//без этого tolower не будет работать для русских букв, находится в locale.h
	setlocale(LC_ALL, "rus"); 
	//преобразуем все буквы в строчные
	for(i = 0; i < len; ++i) 
		findName[i] = tolower(findName[i]);
	
	char buff[30];
	while(1) //пребираем все записи, в поисках нужной (нельзя использовать feof)
	{
		//считываем следующее имя
		if(fread(buff, sizeof(char), 30, file) != 30) 
			break; //достигли конца файла
		
		if(strcmp(findName, buff) == 0) //если оно совпадает с искомым
		{
			Person person;
			fseek(file, -30 * sizeof(char), SEEK_CUR); //перемещаемся в начало записи
			
			//считываем всю запись целиком в person
			if(!fread(&person, sizeof(Person), 1, file)) 
			{ 
				puts("Файл поврежден!"); 
				break; 
			}
			
			//выводим найденую информацию о человеке
			printf("%s имеет возраст %d и получает %d рублей в месяц чистыми.\n", 
											person.surname, person.age,
											(int)round(person.salary * (1.0 - person.tax)));
		}
		else
			//перемещаем файловый указатель на начало новой записи
			fseek(file, sizeof(Person) - 30 * sizeof(char), SEEK_CUR);
	}
	
	if(fclose(file)) 
		puts(ErrorClose), exit(1); 	//закрываем файл
	
	return 0;
}

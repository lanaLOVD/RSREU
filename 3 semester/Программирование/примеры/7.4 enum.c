#include <stdio.h>

// создаем перечисление с ярлыком Direction
//enum Direction {RIGHT, LEFT, DOWN, UP};

// создаем тип перечисления с ярлыком Direction чтобы не писать enum
typedef enum {RIGHT, LEFT, DOWN, UP} Direction;

// создаем переменную dir с перечислимым типом Direction
Direction dir;



//	enum Direction
//    {
//      RIGHT,  // по умолчанию = 0
//      LEFT,   // = 1
//      DOWN,   // = 2
//      UP      // = 3
//    };
  

  
//    enum Direction
//    {
//      RIGHT,    // по умолчанию = 0
//      LEFT = 4, // = 4
//      DOWN,     // = 5
//      UP        // = 6
//    };
  

  
//    enum Direction 
//    {
//      RIGHT = 8,  // = 8
//      LEFT,       // = 9
//      DOWN = 100, // = 100
//      UP          // = 101
//    };
  
    
int main() 
{
	system("chcp 1251");
	

    // присваиваем переменной dir константу UP
    dir = UP;
    
    //можно производить сравнение с константами
    if(dir == UP) 
		puts("Вверх!");
	

    // создаем переменную dir с перечислимым типом Direction
    Direction dir2 = DOWN;
    
    if(dir != dir2) 
		puts("Направления разные!");
    
    
	return 0;
}


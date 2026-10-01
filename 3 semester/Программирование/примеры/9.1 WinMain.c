#include <windows.h>

/*
Чтобы консоль не отображалась, в настройках компилятора нужно явно указать 
что программу нужно запускать в графическом режиме через ключ 
-mwindows
*/



//int main() 
//{
//	MessageBox(NULL,"Hello, World!","Test",MB_OK);
//	return 0;
//}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hpi, LPSTR cmdline, int ss) 
{
	MessageBox(NULL, "Hello, World!", "Test", MB_OK | MB_ICONINFORMATION);
	
	/*
		Функция MessageBox в Windows API используется для отображения модального 
		диалогового окна с сообщением, заголовком и набором кнопок.
		
		int MessageBox(
		    HWND hWnd, 			// дескриптор родительского окна
		    LPCTSTR lpText,		// текст сообщения
		    LPCTSTR lpCaption,	// заголовок диалогового окна
		    UINT uType			// Комбинация флагов, определяющих стиль диалогового окна, включая набор кнопок и иконку
		);
	*/
	return 0;
}
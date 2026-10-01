#include <windows.h>

// Имя класса окна, которое будет использоваться для регистрации и создания окна
const char g_szClassName[] = "myWindowClass";


// Прототип функции обработчика сообщений окна
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Точка входа в программу
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) 
{
    WNDCLASS wc = {0}; // Структура для регистрации класса окна
    HWND hwnd; // Дескриптор окна
    MSG Msg; // Структура для хранения сообщений

    // Заполнение структуры WNDCLASS
    wc.lpfnWndProc   = WndProc; // Указатель на функцию обработчика сообщений
    wc.hInstance     = hInstance; // Дескриптор экземпляра приложения
    wc.lpszClassName = g_szClassName; // Имя класса окна

    // Регистрация класса окна
    if(!RegisterClass(&wc)) 
	{
        // Если регистрация класса окна не удалась, выводим сообщение об ошибке и завершаем программу
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    // Создание окна
    hwnd = CreateWindow(
        g_szClassName, // Имя класса окна
        "The title of my window", // Заголовок окна
        WS_OVERLAPPEDWINDOW, // Стиль окна (обычное перекрывающееся окно)
        CW_USEDEFAULT, CW_USEDEFAULT, // Позиция окна (по умолчанию)
        800, 600, // Размер окна
        NULL, NULL, // Родительское окно и меню (нет)
        hInstance, // Дескриптор экземпляра приложения
        NULL); 

    if(hwnd == NULL) 
	{
        // Если создание окна не удалось, выводим сообщение об ошибке и завершаем программу
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 1;
    }

    // Отображение и обновление окна
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Основной цикл сообщений
    while(GetMessage(&Msg, NULL, 0, 0) > 0) 
	{
        // Перевод и отправка сообщений
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }
    return Msg.wParam;
}

// Обработчик сообщений окна
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
    switch(msg) 
	{
        case WM_PAINT: 
			{
	            // Обработка сообщения WM_PAINT для перерисовки окна
	            PAINTSTRUCT ps;
	            HDC hdc = BeginPaint(hwnd, &ps); // Начало рисования
	            // Закрашиваем клиентскую область 
	            FillRect(hdc, &ps.rcPaint, (HBRUSH) (COLOR_WINDOW+1));
	            EndPaint(hwnd, &ps); // Завершение рисования
	        }
	        return 0;

        case WM_CLOSE:
            // Обработка сообщения WM_CLOSE для закрытия окна
            DestroyWindow(hwnd);
            return 0;

        case WM_DESTROY:
            // Обработка сообщения WM_DESTROY для уничтожения окна
            PostQuitMessage(0);
            return 0;

        default:
            // Обработка всех остальных сообщений по умолчанию
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

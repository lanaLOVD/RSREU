#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define MIN_POINTS 1
#define MAX_POINTS 1000
#define DEFAULT_A 5.0f

// Проверка попадания в область
int inArea(float x, float y, float a) {
    float abs_x = fabs(x);
    
    // Верхний треугольник
    if (y >= 0 && y <= a && y >= abs_x) return 1;
    
    // Нижний треугольник
    if (y <= 0 && y >= -a && y <= -abs_x) return 1;
    
    return 0;
}

// Ручной ввод с использованием указателей
void manualInput(float* points, int n, float min, float max) {
    printf("Введите координаты %d точек (в диапазоне от %.2f до %.2f):\n", n, min, max);
    for (int i = 0; i < n; i++) {
        float x, y;
        do {
            printf("Точка %d (x y): ", i + 1);
            scanf("%f %f", &x, &y);
            if (x < min || x > max || y < min || y > max)
                printf("Ошибка: координаты должны быть в диапазоне [%.2f, %.2f]\n", min, max);
        } while (x < min || x > max || y < min || y > max);
        
        // Используем указательную арифметику для доступа к элементам массива
        *(points + i*2) = x;     // x-координата i-й точки
        *(points + i*2 + 1) = y; // y-координата i-й точки
    }
}

// Случайная генерация с использованием указателей
void randomInput(float* points, int n, float min, float max) {
    srand(time(NULL));
    float range = max - min;
    
    for (int i = 0; i < n; i++) {
        // Используем указательную арифметику
        *(points + i*2) = min + (float)rand() / RAND_MAX * range;     // x
        *(points + i*2 + 1) = min + (float)rand() / RAND_MAX * range; // y
    }
    
    printf("Сгенерированные точки:\n");
    for (int i = 0; i < n; i++) {
        printf("Точка %d: (%.2f, %.2f)\n", i + 1,
               *(points + i*2), *(points + i*2 + 1));
    }
}

// Вывод результатов с использованием указателей
void printResults(float* points, int n, float a) {
    printf("\nРезультаты:\n");
    for (int i = 0; i < n; i++) {
        float x = *(points + i*2);
        float y = *(points + i*2 + 1);
        int result = inArea(x, y, a);
        printf("(%.2f, %.2f) -> %s\n", x, y,
               result ? "В области" : "ВНЕ области");
    }
}

int main(void) {
    int n;
    float a;
    
    printf("Введите параметр a (по умолчанию %.1f): ", DEFAULT_A);
    if (scanf("%f", &a) != 1) {
        a = DEFAULT_A;
        printf("Используется значение по умолчанию: %.1f\n", DEFAULT_A);
    }

    printf("Введите количество точек (%d-%d): ", MIN_POINTS, MAX_POINTS);
    if (scanf("%d", &n) != 1 || n < MIN_POINTS || n > MAX_POINTS) {
        printf("Ошибка: количество точек должно быть от %d до %d\n", MIN_POINTS, MAX_POINTS);
        return 1;
    }

    if (a <= 0) {
        printf("Ошибка: параметр a должен быть положительным\n");
        return 1;
    }

    // Статический массив: каждая точка имеет 2 координаты (x, y)
    static float points[MAX_POINTS][2];

    // Указатель на функцию ввода
    typedef void (*InputFunction)(float*, int, float, float);
    InputFunction inputFunc = NULL;

    int choice;
    printf("Выберите способ ввода (1 - вручную, 2 - случайно): ");
    scanf("%d", &choice);

    float min, max;
    printf("Введите диапазон (min max): ");
    scanf("%f %f", &min, &max);
    
    if (min >= max) {
        printf("Ошибка: min должен быть меньше max\n");
        return 1;
    }

    if (choice == 1) {
        inputFunc = manualInput;
    } else if (choice == 2) {
        inputFunc = randomInput;
    } else {
        printf("Ошибка: неверный выбор\n");
        return 1;
    }

    // Передаем указатель на первый элемент массива
    inputFunc(&points[0][0], n, min, max);

    printResults(&points[0][0], n, a);

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

// Ручной ввод
void manualInput(float points[][2], int n) {
    printf("Введите координаты %d точек:\n", n);
    for (int i = 0; i < n; i++) {
        printf("Точка %d (x y): ", i + 1);
        scanf("%f %f", &points[i][0], &points[i][1]);
    }
}

// Случайная генерация
void randomInput(float points[][2], int n, float min, float max) {
    srand(time(NULL));
    float range = max - min;
    for (int i = 0; i < n; i++) {
        points[i][0] = min + (float)rand() / RAND_MAX * range;
        points[i][1] = min + (float)rand() / RAND_MAX * range;
    }
    printf("Сгенерированные точки:\n");
    for (int i = 0; i < n; i++) {
        printf("Точка %d: (%.2f, %.2f)\n", i + 1, points[i][0], points[i][1]);
    }
}

// Вывод результатов
void printResults(float points[][2], int n, float a) {
    printf("\nРезультаты:\n");
    for (int i = 0; i < n; i++) {
        int result = inArea(points[i][0], points[i][1], a);
        printf("(%.2f, %.2f) -> %s\n",
               points[i][0], points[i][1],
               result ? "В области" : "ВНЕ области");
    }
}

// Основная программа
int main(void) {
    int n, choice;
    float a, min, max;
    static float points[MAX_POINTS][2]; // Двумерный массив: [i][0] = x, [i][1] = y

    printf("Введите параметр a (по умолчанию %.1f): ", DEFAULT_A);
    if (scanf("%f", &a) != 1 || a <= 0) {
        a = DEFAULT_A;
        printf("Используется значение по умолчанию: %.1f\n", DEFAULT_A);
    }

    printf("Введите количество точек (1–%d): ", MAX_POINTS);
    if (scanf("%d", &n) != 1 || n < 1 || n > MAX_POINTS) {
        printf("Ошибка: количество точек должно быть от 1 до %d\n", MAX_POINTS);
        return 1;
    }

    printf("Выберите способ ввода (1 - вручную, 2 - случайно): ");
    scanf("%d", &choice);

    if (choice == 1) {
        manualInput(points, n);
    } else {
        printf("Введите диапазон (min max): ");
        scanf("%f %f", &min, &max);
        if (min >= max) {
            printf("Ошибка: min должен быть меньше max\n");
            return 1;
        }
        randomInput(points, n, min, max);
    }

    printResults(points, n, a);
    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 1. Определяем тип элементов массивов
#define ARRAY_TYPE int

// 2. Определяем макросы для работы с массивами
#define LEN(array) ((array)[0])
#define ELEM(array, i) ((array)[(i) + 1])

// 3. Определяем поведение функций через условную компиляцию
#define REVERSE_SEARCH   // Искать последний элемент вместо первого
// #define SHIFT_RIGHT      // Сдвигать вправо вместо влево (раскомментируйте для включения)

// 4. Подключаем функции для работы с массивами
#include "funcs.inc"

// Функция для вывода массива
void printArray(ARRAY_TYPE** arr, int rows) {
    printf("\nТекущее состояние массива:\n");
    for (int i = 0; i < rows; i++) {
        if (arr[i] != NULL) {
            printf("Строка %d (размер: %d): ", i + 1, LEN(arr[i]));
            for (int j = 0; j < LEN(arr[i]); j++) {
                printf("%d ", ELEM(arr[i], j));
            }
            printf("\n");
        } else {
            printf("Строка %d: NULL (память не выделена)\n", i + 1);
        }
    }
    printf("\n");
}

// Функция для освобождения памяти
void freeArray(ARRAY_TYPE** arr, int rows) {
    if (arr == NULL) return;

    for (int i = 0; i < rows; i++) {
        if (arr[i] != NULL) {
            free(arr[i]);
        }
    }
    free(arr);
}

int main(void) {
    srand(time(NULL));

    int A, B;
    int minVal, maxVal;  // Используем int для удобства ввода

    printf("=== Генерация двумерного массива ===\n");
    printf("Введите количество строк (A): ");
    scanf("%d", &A);
    printf("Введите количество столбцов (B): ");
    scanf("%d", &B);
    printf("Введите минимальное значение диапазона: ");
    scanf("%d", &minVal);
    printf("Введите максимальное значение диапазона: ");
    scanf("%d", &maxVal);

    if (A <= 0 || B <= 0 || minVal > maxVal) {
        printf("Ошибка: некорректные входные данные!\n");
        return 1;
    }

    // Создаем двумерный массив
    ARRAY_TYPE** array = (ARRAY_TYPE**)malloc(A * sizeof(ARRAY_TYPE*));
    if (array == NULL) {
        printf("Ошибка выделения памяти для массива строк!\n");
        return 1;
    }

    // Инициализируем все указатели NULL
    for (int i = 0; i < A; i++) {
        array[i] = NULL;
    }

    // Выделяем память для каждой строки
    for (int i = 0; i < A; i++) {
        array[i] = (ARRAY_TYPE*)malloc((B + 1) * sizeof(ARRAY_TYPE));
        if (array[i] == NULL) {
            printf("Ошибка выделения памяти для строки %d!\n", i + 1);
            freeArray(array, A);
            return 1;
        }

        LEN(array[i]) = B;  // В нулевом элементе храним размер

        for (int j = 0; j < B; j++) {
            ELEM(array[i], j) = minVal + rand() % (maxVal - minVal + 1);
        }
    }

    printf("\nИсходный массив:");
    printArray(array, A);

    // Применяем функции к строкам по циклу
    printf("=== Применение функций к строкам ===\n");

    for (int i = 0; i < A; i++) {
        int functionType = (i % 4) + 1;  // 1-удаление, 2-добавление, 3-перестановка, 4-поиск

        printf("\nОбработка строки %d: ", i + 1);

        switch (functionType) {
            case 1:
                printf("Удаление нечетных элементов\n");
                array[i] = removeOddElements(array[i]);
                break;

            case 2:
                printf("Добавление нулевых элементов в начало\n");
                array[i] = addZeroElements(array[i]);
                break;

            case 3:
                printf("Перестановка нулевых элементов в начало\n");
                moveZerosToFront(array[i]);
                break;

            case 4:
                printf("Зануление элементов со значением %d\n", minVal);
                zeroElementsWithValue(array[i], minVal);
                break;
        }

        if (array[i] != NULL) {
            printf("Результат: размер = %d, элементы: ", LEN(array[i]));
            for (int j = 0; j < LEN(array[i]); j++) {
                printf("%d ", ELEM(array[i], j));
            }
        } else {
            printf("Результат: память не выделена (ошибка realloc)");
        }
        printf("\n");
    }

    printf("\nИтоговый массив:");
    printArray(array, A);

    // Освобождаем память
    freeArray(array, A);

    return 0;
}
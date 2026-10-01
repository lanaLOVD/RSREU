#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

// Функция удаления: удалить все нечетные элементы (без realloc)
void removeOddElements(int* arr) {
    if (arr == NULL)
        return;
    
    int size = arr[0];
    int newSize = 0;
    
    // Считаем четные элементы и переставляем их в начало (начиная с позиции 1)
    for (int i = 1; i <= size; i++) {
        if (arr[i] % 2 == 0) {
            newSize++;
            arr[newSize] = arr[i];
        }
    }
    
    arr[0] = newSize;
}

// Функция добавления: добавить в начало нулевые элементы
void addZeroElements(int* arr, int maxBufferSize) {
    if (arr == NULL) return;
    
    int size = arr[0];
    
    int maxAbs = 0;
    for (int i = 1; i <= size; i++) {
        int absValue = abs(arr[i]);
        if (absValue > maxAbs) {
            maxAbs = absValue;
        }
    }
    
    if (maxAbs == 0) return;
    
    // Проверяем, хватит ли места в буфере
    int newSize = size + maxAbs;
    if (newSize + 1 > maxBufferSize) {
        printf("Ошибка: недостаточно места в буфере для добавления элементов!\n");
        return;
    }
    
    // Сдвигаем существующие элементы вправо на maxAbs позиций
    for (int i = size; i >= 1; i--) {
        arr[i + maxAbs] = arr[i];
    }
    
    // Заполняем начало нулями
    for (int i = 1; i <= maxAbs; i++) {
        arr[i] = 0;
    }
    
    // Обновляем размер
    arr[0] = newSize;
}

// Функция перестановки: переместить все нулевые элементы в начало
void moveZerosToFront(int* arr) {
    if (arr == NULL) return;
    
    int size = arr[0];
    if (size <= 0) return;
    
    int writePos = 1;
    
    // Сначала записываем все нули
    for (int i = 1; i <= size; i++) {
        if (arr[i] == 0) {
            arr[writePos++] = 0;
        }
    }
    
    int* nonZeros = (int*)malloc(size * sizeof(int));
    if (nonZeros == NULL) return;
    
    int nonZeroCount = 0;
    for (int i = 1; i <= size; i++) {
        if (arr[i] != 0) {
            nonZeros[nonZeroCount++] = arr[i];
        }
    }
    
    for (int i = 0; i < nonZeroCount; i++) {
        arr[writePos + i] = nonZeros[i];
    }
    
    free(nonZeros);
}

void zeroElementsWithValue(int* arr, int targetValue) {
    if (arr == NULL) return;
    
    int size = arr[0];
    
    for (int i = 1; i <= size; i++) {
        if (arr[i] == targetValue) {
            arr[i] = 0;
        }
    }
}

void printArray(int** arr, int rows) {
    printf("\nТекущее состояние массива:\n");
    for (int i = 0; i < rows; i++) {
        if (arr[i] != NULL) {
            printf("Строка %d (размер: %d): ", i + 1, arr[i][0]);
            for (int j = 1; j <= arr[i][0]; j++) {
                printf("%d ", arr[i][j]);
            }
            printf("\n");
        } else {
            printf("Строка %d: NULL (память не выделена)\n", i + 1);
        }
    }
    printf("\n");
}

// Функция для освобождения памяти
void freeArray(int** arr, int rows) {
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
    
    int A, B, minVal, maxVal;
    
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
    int** array = (int**)malloc(A * sizeof(int*));
    if (array == NULL) {
        printf("Ошибка выделения памяти для массива строк!\n");
        return 1;
    }
    
    // Инициализируем все указатели NULL
    for (int i = 0; i < A; i++) {
        array[i] = NULL;
    }
    
    int maxPossibleAbs = (abs(minVal) > abs(maxVal)) ? abs(minVal) : abs(maxVal);
    int bufferSize = B + maxPossibleAbs + 1;
    
    for (int i = 0; i < A; i++) {
        array[i] = (int*)malloc(bufferSize * sizeof(int));
        if (array[i] == NULL) {
            printf("Ошибка выделения памяти для строки %d!\n", i + 1);
            freeArray(array, A);
            return 1;
        }
        
        array[i][0] = B; // В нулевом элементе храним размер
        
        for (int j = 1; j <= B; j++) {
            array[i][j] = minVal + rand() % (maxVal - minVal + 1);
        }
    }
    
    printf("\nИсходный массив:");
    printArray(array, A);
    
    // Применяем функции к строкам по циклу
    printf("=== Применение функций к строкам ===\n");
    
    for (int i = 0; i < A; i++) {
        int functionType = (i % 4) + 1; // 1-удаление, 2-добавление, 3-перестановка, 4-поиск
        
        printf("\nОбработка строки %d: ", i + 1);
        
        switch (functionType) {
            case 1:
                printf("Удаление нечетных элементов\n");
                removeOddElements(array[i]);
                break;
                
            case 2:
                printf("Добавление нулевых элементов в начало\n");
                addZeroElements(array[i], bufferSize);
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
            printf("Результат: размер = %d, элементы: ", array[i][0]);
            for (int j = 1; j <= array[i][0]; j++) {
                printf("%d ", array[i][j]);
            }
        } else {
            printf("Результат: память не выделена");
        }
        printf("\n");
    }
    
    printf("\nИтоговый массив:");
    printArray(array, A);
    
    // Освобождаем память
    freeArray(array, A);
    
    return 0;
}

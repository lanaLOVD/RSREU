#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Функция для выделения памяти под массив
int* allocateMemory(int size) {
    return (int*)malloc(size * sizeof(int));
}

// Функция для освобождения памяти
void freeMemory(int* array) {
    if (array != NULL) {
        free(array);
    }
}

// Функция для заполнения массива случайными значениями [0; 999]
void fillArrayRandom(int* array, int size) {
    for (int i = 0; i < size; i++) {
        array[i] = rand() % 1000;
    }
}

// Функция для вывода массива
void printArray(const int* array, int size) {
    if (size == 0) {
        printf("Массив пуст\n");
        return;
    }
    
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// Функция для вычисления среднего арифметического
double calcAverage(const int* array, int size) {
    if (size == 0) {
        return 0.0;
    }
    
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum / size;
}

// Функция для подсчета количества цифр в числе
int countDigits(int number) {
    if (number == 0) {
        return 1;
    }
    
    int count = 0;
    int temp = abs(number);
    while (temp > 0) {
        count++;
        temp /= 10;
    }
    return count;
}

// Функция для проверки, имеет ли число четное количество цифр
int hasEvenNumberOfDigits(int number) {
    return (countDigits(number) % 2 == 0);
}

// Функция для создания массива B (числа меньше среднего)
int* createArrayB(const int* arrayA, int sizeA, double average, int* sizeB) {
    // Сначала подсчитаем, сколько элементов подходит
    int count = 0;
    for (int i = 0; i < sizeA; i++) {
        if (arrayA[i] < average) {
            count++;
        }
    }
    
    *sizeB = count;
    
    if (count == 0) {
        return NULL;
    }
    
    // Выделяем память под массив B
    int* arrayB = allocateMemory(count);
    if (arrayB == NULL) {
        *sizeB = 0;
        return NULL;
    }
    
    // Заполняем массив B
    int index = 0;
    for (int i = 0; i < sizeA; i++) {
        if (arrayA[i] < average) {
            arrayB[index] = arrayA[i];
            index++;
        }
    }
    
    return arrayB;
}

// Функция для перемещения элементов с четным количеством цифр в начало
int moveEvenDigitsToFront(int* array, int size) {
    if (size <= 1) {
        return 0;
    }
    
    // Используем алгоритм разделения (подобный partition в QuickSort)
    int left = 0;
    int right = size - 1;
    int movedCount = 0;
    
    while (left < right) {
        // Находим первый элемент слева, у которого нечетное количество цифр
        while (left < size && hasEvenNumberOfDigits(array[left])) {
            left++;
            movedCount++;
        }
        
        // Находим первый элемент справа, у которого четное количество цифр
        while (right >= 0 && !hasEvenNumberOfDigits(array[right])) {
            right--;
        }
        
        // Меняем местами, если индексы не пересеклись
        if (left < right) {
            int temp = array[left];
            array[left] = array[right];
            array[right] = temp;
            movedCount++;
            left++;
            right--;
        }
    }
    
    // Корректируем счетчик: если все элементы четные, movedCount будет равен size
    if (movedCount > size) {
        movedCount = size;
    }
    
    return movedCount;
}

int main(void) {
    srand(time(NULL));
    
    int sizeA;
    
    // Ввод размера массива A
    printf("Введите размер массива A (от 1 до 100): ");
    scanf("%d", &sizeA);
    
    if (sizeA < 1 || sizeA > 100) {
        printf("Ошибка: размер массива должен быть от 1 до 100.\n");
        return 1;
    }
    
    // 1. Создание и заполнение массива A
    int* arrayA = allocateMemory(sizeA);
    if (arrayA == NULL) {
        printf("Ошибка выделения памяти для массива A!\n");
        return 1;
    }
    
    fillArrayRandom(arrayA, sizeA);
    printf("\n=== Массив A ===\n");
    printf("Размер: %d\n", sizeA);
    printf("Элементы: ");
    printArray(arrayA, sizeA);
    
    // 2. Вычисление среднего арифметического массива A
    double average = calcAverage(arrayA, sizeA);
    printf("Среднее арифметическое: %.2f\n", average);
    
    // 3. Создание массива B (элементы меньше среднего)
    int sizeB;
    int* arrayB = createArrayB(arrayA, sizeA, average, &sizeB);
    
    printf("\n=== Массив B ===\n");
    printf("Размер: %d\n", sizeB);
    
    if (sizeB == 0 || arrayB == NULL) {
        printf("В массиве B нет элементов (все числа >= среднего)\n");
    } else {
        printf("Исходные элементы: ");
        printArray(arrayB, sizeB);
        
        // 4. Перемещение элементов с четным количеством цифр в начало
        int movedCount = moveEvenDigitsToFront(arrayB, sizeB);
        printf("Перемещено элементов с четным количеством цифр: %d\n", movedCount);
        printf("Массив B после перемещения: ");
        printArray(arrayB, sizeB);
        
        // 5. Вывод информации о количестве цифр для каждого элемента
        printf("\nИнформация о количестве цифр:\n");
        for (int i = 0; i < sizeB; i++) {
            int digits = countDigits(arrayB[i]);
            printf("arrayB[%d] = %d, цифр: %d (%s)\n",
                   i, arrayB[i], digits,
                   (digits % 2 == 0) ? "четное" : "нечетное");
        }
    }
    
    // 6. Освобождение памяти
    freeMemory(arrayA);
    freeMemory(arrayB);
    
    printf("\nПамять успешно освобождена.\n");
    
    return 0;
}

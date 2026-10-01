#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

// Функция для проверки, является ли символ разделителем
bool is_delimiter(char c) {
    return c == ' ' || c == ',' || c == '.' || c == '!' || c == '?' || c == '\0';
}

// Функция для проверки, является ли символ буквой
bool is_letter(char c) {
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

// Функция для проверки, является ли символ цифрой
bool is_digit(char c) {
    return c >= '0' && c <= '9';
}

// Функция для преобразования символа в нижний регистр
char to_lower(char c) {
    if (c >= 'A' && c <= 'Z') {
        return c + ('a' - 'A');
    }
    return c;
}

// ==================== ФУНКЦИИ ДЛЯ КОМАНД ====================

// 1. Функция для команды -info: общее количество иных последовательностей
int count_other_sequences(const char* text) {
    int count = 0;
    int i = 0;
    int len = strlen(text);
    
    while (i < len) {
        // Пропускаем разделители
        while (i < len && is_delimiter(text[i])) {
            i++;
        }
        
        if (i >= len) break;
        
        // Проверяем тип последовательности
        bool is_word = true;
        bool is_number = true;
        int start = i;
        
        while (i < len && !is_delimiter(text[i])) {
            if (!is_letter(text[i])) {
                is_word = false;
            }
            if (!is_digit(text[i])) {
                is_number = false;
            }
            i++;
        }
        
        // Если не слово и не число - это иная последовательность
        if (!is_word && !is_number) {
            count++;
        }
    }
    
    return count;
}

// 2. Функция для команды -create: создание массива чисел меньше M
int* create_numbers_less_than_m(const char* text, int m, int* result_count) {
    // Сначала подсчитаем, сколько чисел меньше M
    int count = 0;
    int i = 0;
    int len = strlen(text);
    
    while (i < len) {
        // Пропускаем разделители
        while (i < len && is_delimiter(text[i])) {
            i++;
        }
        
        if (i >= len) break;
        
        // Проверяем, является ли последовательность числом
        bool is_number = true;
        int start = i;
        
        while (i < len && !is_delimiter(text[i])) {
            if (!is_digit(text[i])) {
                is_number = false;
            }
            i++;
        }
        
        // Если это число, преобразуем его и проверяем
        if (is_number && (i - start) > 0) {
            // Создаем временную строку для числа
            char* num_str = (char*)malloc((i - start + 1) * sizeof(char));
            strncpy(num_str, &text[start], i - start);
            num_str[i - start] = '\0';
            
            int num = atoi(num_str);
            free(num_str);
            
            if (num < m) {
                count++;
            }
        }
    }
    
    // Если чисел не найдено
    if (count == 0) {
        *result_count = 0;
        return NULL;
    }
    
    // Выделяем память для массива
    int* numbers = (int*)malloc(count * sizeof(int));
    if (!numbers) {
        *result_count = 0;
        return NULL;
    }
    
    // Заполняем массив
    i = 0;
    int idx = 0;
    
    while (i < len) {
        // Пропускаем разделители
        while (i < len && is_delimiter(text[i])) {
            i++;
        }
        
        if (i >= len) break;
        
        // Проверяем, является ли последовательность числом
        bool is_number = true;
        int start = i;
        
        while (i < len && !is_delimiter(text[i])) {
            if (!is_digit(text[i])) {
                is_number = false;
            }
            i++;
        }
        
        // Если это число, преобразуем его и проверяем
        if (is_number && (i - start) > 0) {
            // Создаем временную строку для числа
            char* num_str = (char*)malloc((i - start + 1) * sizeof(char));
            strncpy(num_str, &text[start], i - start);
            num_str[i - start] = '\0';
            
            int num = atoi(num_str);
            free(num_str);
            
            if (num < m) {
                numbers[idx++] = num;
            }
        }
    }
    
    *result_count = count;
    return numbers;
}

// 3. Функция для команды -delete: удаление слов, содержащих заданную последовательность букв
char* delete_words_with_sequence(const char* text, const char* sequence) {
    int text_len = strlen(text);
    int seq_len = strlen(sequence);
    
    // Создаем копию последовательности в нижнем регистре для сравнения
    char* seq_lower = (char*)malloc((seq_len + 1) * sizeof(char));
    for (int i = 0; i < seq_len; i++) {
        seq_lower[i] = to_lower(sequence[i]);
    }
    seq_lower[seq_len] = '\0';
    
    // Выделяем память для результата (максимальная длина - исходная длина)
    char* result = (char*)malloc((text_len + 1) * sizeof(char));
    if (!result) {
        free(seq_lower);
        return NULL;
    }
    
    int i = 0;
    int result_idx = 0;
    
    while (i < text_len) {
        // Копируем разделители как есть
        while (i < text_len && is_delimiter(text[i])) {
            result[result_idx++] = text[i++];
        }
        
        if (i >= text_len) break;
        
        // Определяем границы слова
        int start = i;
        bool is_word = true;
        
        while (i < text_len && !is_delimiter(text[i])) {
            if (!is_letter(text[i])) {
                is_word = false;
            }
            i++;
        }
        
        int end = i;
        
        // Если это не слово, копируем как есть
        if (!is_word) {
            for (int j = start; j < end; j++) {
                result[result_idx++] = text[j];
            }
        } else {
            // Проверяем, содержит ли слово заданную последовательность
            bool contains_sequence = false;
            
            // Проверяем все возможные подстроки слова
            for (int j = start; j <= end - seq_len; j++) {
                bool match = true;
                for (int k = 0; k < seq_len; k++) {
                    if (to_lower(text[j + k]) != seq_lower[k]) {
                        match = false;
                        break;
                    }
                }
                if (match) {
                    contains_sequence = true;
                    break;
                }
            }
            
            // Если слово не содержит последовательность, копируем его
            if (!contains_sequence) {
                for (int j = start; j < end; j++) {
                    result[result_idx++] = text[j];
                }
            }
            // Иначе пропускаем (удаляем) слово
        }
    }
    
    // Завершаем строку
    result[result_idx] = '\0';
    
    free(seq_lower);
    return result;
}

// ==================== ОСНОВНАЯ ФУНКЦИЯ ====================

int main(int argc, char* argv[]) {
    // Проверка наличия минимального количества аргументов
    if (argc < 3) {
        printf("Ошибка: недостаточно аргументов.\n");
        printf("Формат запуска: Lab9.exe \"Текст\" -команда [аргументы]\n");
        printf("Доступные команды:\n");
        printf("  -info - вывод количества иных последовательностей\n");
        printf("  -create M - создание массива чисел меньше M\n");
        printf("  -delete последовательность - удаление слов, содержащих последовательность\n");
        return 1;
    }
    
    char* text = argv[1];
    char* command = argv[2];
    
    // Команда -info
    if (strcmp(command, "-info") == 0) {
        if (argc != 3) {
            printf("Ошибка: для команды -info не нужны дополнительные аргументы.\n");
            printf("Использование: Lab9.exe \"Текст\" -info\n");
            return 1;
        }
        
        int count = count_other_sequences(text);
        printf("Количество иных последовательностей: %d\n", count);
    }
    // Команда -create
    else if (strcmp(command, "-create") == 0) {
        if (argc != 4) {
            printf("Ошибка: для команды -create требуется один дополнительный аргумент M.\n");
            printf("Использование: Lab9.exe \"Текст\" -create M\n");
            return 1;
        }
        
        int m = atoi(argv[3]);
        if (m == 0 && strcmp(argv[3], "0") != 0) {
            printf("Ошибка: M должно быть целым числом.\n");
            return 1;
        }
        
        int count;
        int* numbers = create_numbers_less_than_m(text, m, &count);
        
        if (count == 0) {
            printf("Числа меньше %d не найдены.\n", m);
        } else {
            printf("Массив чисел меньше %d (%d элементов):\n", m, count);
            printf("[");
            for (int i = 0; i < count; i++) {
                printf("%d", numbers[i]);
                if (i < count - 1) {
                    printf(", ");
                }
            }
            printf("]\n");
        }
        
        free(numbers);
    }
    // Команда -delete
    else if (strcmp(command, "-delete") == 0) {
        if (argc != 4) {
            printf("Ошибка: для команды -delete требуется один дополнительный аргумент (последовательность букв).\n");
            printf("Использование: Lab9.exe \"Текст\" -delete последовательность\n");
            return 1;
        }
        
        char* sequence = argv[3];
        
        // Проверяем, что последовательность состоит только из букв
        for (int i = 0; sequence[i] != '\0'; i++) {
            if (!is_letter(sequence[i])) {
                printf("Ошибка: последовательность должна состоять только из букв.\n");
                return 1;
            }
        }
        
        char* result = delete_words_with_sequence(text, sequence);
        printf("Текст после удаления слов, содержащих \"%s\":\n", sequence);
        printf("%s\n", result);
        
        free(result);
    }
    // Неизвестная команда
    else {
        printf("Ошибка: неизвестная команда \"%s\".\n", command);
        printf("Доступные команды: -info, -create, -delete\n");
        return 1;
    }
    
    return 0;
}

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Функция сортировки подсчетом
void CountSort(vector<int>& A) {
    // Находим максимальный элемент в массиве
    int maxElem = *max_element(A.begin(), A.end());
    
    // Создаем массив для подсчета, размером maxElem + 1
    vector<int> count(maxElem + 1);

    // Подсчитываем количество вхождений каждого элемента
    for (int x : A) {
        count[x] += 1;
    }

    // Очищаем исходный массив для заполнения отсортированными элементами
    A.clear();

    // Восстанавливаем отсортированный массив из счетчиков
    for (int i = 0; i != maxElem + 1; ++i) {
        // Добавляем элемент i столько раз, сколько он встречался
        for (int j = 0; j != count[i]; j++) {
            A.push_back(i);
        }
    }
}

int main() {
    int x;
    vector<int> numbers;

    // Чтение чисел из входного потока до конца ввода
    while (cin >> x) {
        numbers.push_back(x);
    }

    // Сортировка подсчетом
    CountSort(numbers);

    // Вывод отсортированного массива
    for (size_t i = 0; i != numbers.size(); ++i) {
        if (i + 1 != numbers.size()) {
            cout << numbers[i] << " ";
        }
        else {
            cout << numbers[i];
        }
    }
    
    return 0;
}

#include <iostream>
#include <vector>

// Использование пространства имен std для упрощения кода
using namespace std;

// Функция сортировки вставками в порядке неубывания (возрастания)
void InsertionSort(vector<int> A) {
    // Начинаем со второго элемента (индекс 1)
    for (size_t i = 1; i != A.size(); ++i) {
        size_t j = i;
        int elem = A.at(i);  // Сохраняем текущий элемент
        
        // Сдвигаем элементы, которые больше текущего, вправо
        while (j > 0 && A.at(j - 1) > elem) {
            A.at(j) = A.at(j - 1);
            --j;
        }
        // Вставляем сохраненный элемент на правильную позицию
        A.at(j) = elem;
    }

    // Вывод отсортированного массива
    for (const int number : A) {
        cout << number << " ";
    }
}

int main() {
    int x;
    vector<int> numbers;
    
    // Чтение чисел из входного потока до конца ввода
    while (cin >> x) {
        numbers.push_back(x);
    }
    
    // Вызов функции сортировки вставками
    InsertionSort(numbers);
    
    return 0;
}

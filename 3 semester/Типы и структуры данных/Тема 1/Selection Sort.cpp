#include <iostream>
#include <vector>

// Использование пространства имен std для упрощения кода
using namespace std;

// Функция сортировки выбором в порядке невозрастания (убывания)
void SelectionSort(vector<int> A) {
    // Внешний цикл: проходим по всем элементам массива, кроме последнего
    for (size_t i = 0; i + 1 != A.size(); ++i) {
        // Предполагаем, что текущий элемент - максимальный
        int maxElem = A.at(i);
        size_t ind = i;
        
        // Внутренний цикл: ищем максимальный элемент в оставшейся части массива
        for (size_t j = i + 1; j != A.size(); ++j) {
            if (A.at(j) > maxElem) {
                // Нашли элемент больше текущего максимума
                maxElem = A.at(j);
                ind = j; // Запоминаем индекс нового максимума
            }
        }
        
        // Если нашли элемент больше текущего, меняем их местами
        if (i != ind) {
            swap(A.at(ind), A.at(i));
        }
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
    
    // Вызов функции сортировки выбором
    SelectionSort(numbers);
    
    return 0;
}

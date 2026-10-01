#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

// Функция слияния двух отсортированных массивов в один отсортированный
vector<int> merge(const vector<int>& left, const vector<int>& right) {
    vector<int> res;  // Результирующий вектор
    int i = 0, j = 0; // Индексы для прохода по left и right
    
    // Слияние пока есть элементы в обоих массивах
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) {
            res.push_back(left[i]);  // Берем элемент из левой части
            i++;
        } else {
            res.push_back(right[j]); // Берем элемент из правой части
            j++;
        }
    }
    
    // Добавляем оставшиеся элементы из левой части (если есть)
    while (i < left.size()) {
        res.push_back(left[i]);
        i++;
    }
    
    // Добавляем оставшиеся элементы из правой части (если есть)
    while (j < right.size()) {
        res.push_back(right[j]);
        j++;
    }
    
    return res;
}

// Рекурсивная сортировка слиянием
vector<int> merge_sort(const vector<int>& arr) {
    // Базовый случай: массив из 0 или 1 элемента уже отсортирован
    if (arr.size() <= 1) return arr;
    
    // Находим середину массива
    int mid = arr.size() / 2;
    
    // Делим массив на две части
    vector<int> left(arr.begin(), arr.begin() + mid);
    vector<int> right(arr.begin() + mid, arr.end());
    
    // Рекурсивно сортируем обе части и сливаем результаты
    return merge(merge_sort(left), merge_sort(right));
}

int main() {
    int n;
    cin >> n;                   // Читаем количество элементов
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];          // Читаем массив
    }

    arr = merge_sort(arr);      // Сортируем слиянием

    // Выводим отсортированный массив
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}

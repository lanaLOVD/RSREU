#include <iostream>
#include <vector>
#include <cstdlib>   // для rand()
#include <ctime>     // для srand()
using namespace std;

// Функция быстрой сортировки
void quick_sort(vector<int>& arr, int left, int right) {
    // Базовый случай: если подмассив содержит более одного элемента
    if (left < right) {
        int l = left;   // Левый указатель (начинается с левой границы)
        int r = right;  // Правый указатель (начинается с правой границы)
        
        // Выбор случайного опорного элемента (pivot)
        int val = arr[left + rand() % (right - left + 1)];
        
        // Разделение массива относительно опорного элемента
        while (l <= r) {
            // Двигаем левый указатель вправо, пока элементы меньше опорного
            while (arr[l] < val) l++;
            
            // Двигаем правый указатель влево, пока элементы больше опорного
            while (arr[r] > val) r--;
            
            // Если указатели не пересеклись, меняем элементы местами
            if (l <= r) {
                swap(arr[l], arr[r]);
                l++;
                r--;
            }
        }
        
        // Рекурсивно сортируем левую и правую части
        // Левая часть: от left до r
        if (left < r) quick_sort(arr, left, r);
        // Правая часть: от l до right
        if (right > l) quick_sort(arr, l, right);
    }
}

int main() {
    srand(time(0));  // Инициализация генератора случайных чисел текущим временем

    int n;
    cin >> n;                     // Читаем количество элементов
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];            // Читаем массив
    }

    quick_sort(arr, 0, n - 1);    // Сортируем весь массив

    // Выводим отсортированный массив
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;

    return 0;
}

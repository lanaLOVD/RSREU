#include <iostream>
#include <vector>
using namespace std;

// Функция для восстановления свойства кучи в поддереве с корнем i
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;        // Инициализируем наибольший элемент как корень
    int left = 2 * i + 1;   // Левый потомок
    int right = 2 * i + 2;  // Правый потомок
    
    // Если левый потомок существует и больше текущего наибольшего
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }
    
    // Если правый потомок существует и больше текущего наибольшего
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }
    
    // Если наибольший элемент не корень
    if (largest != i) {
        swap(arr[i], arr[largest]);  // Меняем местами
        heapify(arr, n, largest);    // Рекурсивно heapify затронутое поддерево
    }
}

// Основная функция пирамидальной сортировки
void heapSort(vector<int>& arr) {
    int n = arr.size();
    
    // Построение max-heap (перегруппировка массива)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);  // Heapify начиная с последнего не-листового узла
    }
    
    // Извлечение элементов из кучи один за другим
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);  // перемещаем текущий корень (максимум) в конец
        heapify(arr, i, 0);    // вызываем heapify на уменьшенной куче
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    vector<int> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    heapSort(arr);  // Сортируем массив
    
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";  // Выводим отсортированный массив
    }
    cout << "\n";
    
    return 0;
}

#include <iostream>
#include <vector>
using namespace std;

class MaxHeap {
private:
    vector<int> heap;  // Вектор для хранения элементов кучи
    
    // Всплытие элемента вверх
    void siftUp(int index) {
        while (index > 0) {
            int parent = (index - 1) / 2;  // Индекс родителя
            if (heap[parent] >= heap[index]) break;  // Если родитель больше или равен - остановка
            swap(heap[parent], heap[index]);  // Меняем местами с родителем
            index = parent;  // Переходим к родительской позиции
        }
    }
    
    // Погружение элемента вниз
    void siftDown(int index) {
        int size = heap.size();
        while (index * 2 + 1 < size) {  // Пока есть хотя бы один потомок
            int left = index * 2 + 1;   // Левый потомок
            int right = index * 2 + 2;  // Правый потомок
            int maxChild = left;        // Предполагаем, что левый - наибольший
            
            // Если правый потомок существует и больше левого
            if (right < size && heap[right] > heap[left]) {
                maxChild = right;
            }
            
            // Если текущий элемент уже больше наибольшего потомка - остановка
            if (heap[index] >= heap[maxChild]) break;
            
            swap(heap[index], heap[maxChild]);  // Меняем местами с наибольшим потомком
            index = maxChild;  // Переходим к позиции потомка
        }
    }
    
public:
    // Вставка нового элемента
    void insert(int value) {
        heap.push_back(value);  // Добавляем в конец
        siftUp(heap.size() - 1);  // Всплываем на нужную позицию
    }
    
    // Извлечение максимального элемента
    int extract() {
        int maxValue = heap[0];  // Максимум всегда в корне
        heap[0] = heap.back();   // Последний элемент ставим в корень
        heap.pop_back();         // Удаляем последний элемент
        if (!heap.empty()) {
            siftDown(0);  // Погружаем корневой элемент на нужную позицию
        }
        return maxValue;
    }
};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n;
    cin >> n;
    
    MaxHeap heap;
    
    for (int i = 0; i < n; i++) {
        int command;
        cin >> command;
        
        if (command == 0) {
            int value;
            cin >> value;
            heap.insert(value);  // Вставка элемента
        } else {
            cout << heap.extract() << "\n";  // Извлечение максимума
        }
    }
    
    return 0;
}

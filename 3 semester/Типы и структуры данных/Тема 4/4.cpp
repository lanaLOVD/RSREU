#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main() {
    priority_queue<int> heap;  // по умолчанию max-heap (максимальная куча)
    string command;
    
    while (cin >> command) {
        if (command == "CLEAR") {
            // Создаем новую пустую очередь
            heap = priority_queue<int>();  // Альтернативный способ очистки
        }
        else if (command == "ADD") {
            int n;
            cin >> n;
            heap.push(n);  // Добавляем элемент в кучу
        }
        else if (command == "EXTRACT") {
            if (heap.empty()) {
                cout << "CANNOT" << endl;  // Если куча пуста
            } else {
                cout << heap.top() << endl;  // Извлекаем максимальный элемент
                heap.pop();  // Удаляем его из кучи
            }
        }
    }
    
    return 0;
}

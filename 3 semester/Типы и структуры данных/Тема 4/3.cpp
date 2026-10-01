#include <iostream>
#include <queue>
#include <string>
#include <functional>

using namespace std;

int main() {
    // Создаем минимальную кучу (min-heap)
    priority_queue<int, vector<int>, greater<int>> min_heap;
    string command;
    
    while (cin >> command) {
        if (command == "CLEAR") {
            // Очищаем пирамиду
            while (!min_heap.empty()) {
                min_heap.pop();
            }
        }
        else if (command == "ADD") {
            int n;
            cin >> n;
            min_heap.push(n);  // Добавляем элемент в кучу
        }
        else if (command == "EXTRACT") {
            if (min_heap.empty()) {
                cout << "CANNOT" << endl;  // Если куча пуста
            }
            else {
                cout << min_heap.top() << endl;  // Извлекаем минимальный элемент
                min_heap.pop();
            }
        }
    }
    
    return 0;
}

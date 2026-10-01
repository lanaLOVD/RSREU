#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    // Создаем минимальную кучу для хранения чисел
    priority_queue<double, vector<double>, greater<double>> min_heap;
    
    // Читаем все числа и добавляем их в кучу
    for (int i = 0; i < n; i++) {
        double num;
        cin >> num;
        min_heap.push(num);
    }
    
    double total_cost = 0.0;  // Общая стоимость соединений
    
    // Пока в куче больше одного элемента
    while (min_heap.size() > 1) {
        // Извлекаем два наименьших элемента
        double a = min_heap.top(); min_heap.pop();
        double b = min_heap.top(); min_heap.pop();
        
        // Складываем их
        double sum = a + b;
        // Вычисляем стоимость соединения (5% от суммы)
        double cost = sum * 0.05;
        total_cost += cost;  // Добавляем к общей стоимости
        
        // Помещаем сумму обратно в кучу
        min_heap.push(sum);
    }
    
    // Выводим общую стоимость с точностью до 2 знаков после запятой
    cout << fixed << setprecision(2) << total_cost << endl;
    
    return 0;
}

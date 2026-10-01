#include <iostream>
#include <set>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);  // Ускоряем ввод/вывод
    cin.tie(NULL);                     // Отключаем привязку cin к cout
    
    int n;  // Количество операций
    cin >> n;
    
    set<int> s;                 // Множество для хранения чисел
    char operation;             // Операция (+ или ?)
    int value;                  // Значение для операции
    long long last_answer = 0;  // Храним последний ответ на запрос '?'
    bool prev_was_query = false; // Флаг: была ли предыдущая операция запросом '?'
    
    for (int i = 0; i < n; i++) {
        cin >> operation >> value;
        
        if (operation == '+') {
            // Операция добавления
            if (prev_was_query) {
                // Если предыдущая операция была запросом,
                // то добавляем (value + last_answer) mod 10^9
                // Это изменяет значение по особому правилу
                value = (value + last_answer) % 1000000000;
            }
            s.insert(value);      // Добавляем значение в множество
            prev_was_query = false; // Сбрасываем флаг (текущая операция - не запрос)
        } else { // operation == '?'
            // Операция запроса: найти наименьшее число ≥ value
            auto it = s.lower_bound(value);  // Ищем первый элемент ≥ value
            
            if (it == s.end()) {
                // Если такого элемента нет
                last_answer = -1;
            } else {
                // Нашли элемент
                last_answer = *it;
            }
            
            cout << last_answer << "\n";  // Выводим ответ
            prev_was_query = true;        // Устанавливаем флаг (текущая операция - запрос)
        }
    }
    
    return 0;
}
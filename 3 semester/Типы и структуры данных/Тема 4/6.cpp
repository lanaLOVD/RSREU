#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    // Вектор для хранения событий: время и тип события
    vector<pair<int, int>> timeline;
    
    for (int i = 0; i < n; i++) {
        int t, l;
        cin >> t >> l;
        timeline.push_back({t, 1});        // начало обработки (+1 аппарат)
        timeline.push_back({t + l, -1});   // окончание обработки (-1 аппарат)
    }
    
    // Сортируем события по времени
    // При равенстве времени: сначала окончания, потом начала
    sort(timeline.begin(), timeline.end(),
         [](const pair<int, int>& a, const pair<int, int>& b) {
             if (a.first == b.first) return a.second < b.second;
             return a.first < b.first;
         });
    
    int current_apparatus = 0;  // Текущее количество занятых аппаратов
    int max_apparatus = 0;      // Максимальное количество занятых аппаратов
    
    // Обрабатываем все события по порядку
    for (auto& event : timeline) {
        current_apparatus += event.second;  // Добавляем или убираем аппарат
        max_apparatus = max(max_apparatus, current_apparatus);  // Обновляем максимум
    }
    
    cout << max_apparatus << endl;
    
    return 0;
}

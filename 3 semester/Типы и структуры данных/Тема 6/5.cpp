#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Глобальные переменные для удобства доступа в DFS
vector<vector<int>> graph;  // Список смежности графа
vector<bool> visited;       // Массив посещенных вершин
vector<int> component;      // Временный вектор для хранения текущей компоненты связности

// Функция обхода в глубину для поиска компоненты связности
// v - текущая вершина
void dfs(int v) {
    visited[v] = true;          // Помечаем вершину как посещенную
    component.push_back(v);     // Добавляем вершину в текущую компоненту
    
    // Обходим всех соседей вершины v
    for (int u : graph[v]) {
        if (!visited[u]) {      // Если соседняя вершина еще не посещена
            dfs(u);             // Рекурсивно запускаем DFS из нее
        }
    }
}

int main() {
    // Оптимизация ввода/вывода для ускорения работы
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int n, m; // n - количество вершин, m - количество ребер
    cin >> n >> m;
    
    // Инициализация структур данных
    // Индексация вершин с 1 до n (поэтому размер n+1)
    graph.resize(n + 1);
    visited.resize(n + 1, false);
    
    // Построение графа (списка смежности)
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        
        // Добавляем ребра в обе стороны, так как граф неориентированный
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    // Вектор для хранения всех компонент связности
    vector<vector<int>> components;
    
    // Поиск компонент связности
    for (int i = 1; i <= n; i++) {
        // Если вершина еще не посещена, значит она принадлежит новой компоненте
        if (!visited[i]) {
            component.clear();   // Очищаем временный вектор для новой компоненты
            dfs(i);              // Запускаем DFS из этой вершины
            
            // Добавляем найденную компоненту в список всех компонент
            components.push_back(component);
        }
    }
    
    // Вывод результата
    // Сначала выводим количество компонент связности
    cout << components.size() << "\n";
    
    // Для каждой компоненты выводим:
    for (auto& comp : components) {
        // 1. Количество вершин в компоненте
        cout << comp.size() << "\n";
        
        // 2. Сами вершины компоненты
        for (int vertex : comp) {
            cout << vertex << " ";
        }
        cout << "\n";
    }
    
    return 0;
}

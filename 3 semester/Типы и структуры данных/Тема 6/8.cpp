#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main() {
    int n; // Количество вершин в графе
    cin >> n;
    
    // Матрица смежности графа
    // graph[i][j] = 1, если есть ребро из i в j, иначе 0
    vector<vector<int>> graph(n, vector<int>(n));
    
    // Чтение матрицы смежности
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }
    
    int start, end; // Начальная и конечная вершины
    cin >> start >> end;
    
    // Переводим в 0-индексацию для удобства работы с массивами
    start--;
    end--;
    
    // Массив расстояний: dist[i] = расстояние от start до i
    // -1 означает, что вершина еще не посещена
    vector<int> dist(n, -1);
    
    // Массив предков: pred[i] = вершина, из которой мы пришли в i
    // Используется для восстановления пути
    vector<int> pred(n, -1);
    
    // Очередь для BFS (обхода в ширину)
    queue<int> q;
    
    // Начинаем с начальной вершины
    dist[start] = 0;
    q.push(start);
    
    // BFS (обход в ширину)
    while (!q.empty()) {
        int node = q.front(); // Берем вершину из начала очереди
        q.pop();
        
        // Проверяем всех соседей текущей вершины
        for (int neighbor = 0; neighbor < n; neighbor++) {
            // Если есть ребро и соседняя вершина еще не посещена
            if (graph[node][neighbor] == 1 && dist[neighbor] == -1) {
                // Обновляем расстояние до соседней вершины
                dist[neighbor] = dist[node] + 1;
                
                // Запоминаем, откуда мы пришли (для восстановления пути)
                pred[neighbor] = node;
                
                // Добавляем соседа в очередь для дальнейшего обхода
                q.push(neighbor);
            }
        }
    }
    
    // Если путь не найден (dist[end] остался -1)
    if (dist[end] == -1) {
        cout << -1 << endl;
        return 0;
    }
    
    // Выводим длину кратчайшего пути
    cout << dist[end] << endl;
    
    // Если путь существует и его длина больше 0
    if (dist[end] > 0) {
        // Восстанавливаем путь от end к start
        vector<int> path;
        int current = end; // Начинаем с конечной вершины
        
        // Идем по цепочке предков до начальной вершины
        while (current != -1) {
            path.push_back(current);
            current = pred[current]; // Переходим к предку
        }
        
        // Разворачиваем путь, так как мы шли от конца к началу
        reverse(path.begin(), path.end());
        
        // Выводим путь, переводя обратно в 1-индексацию
        for (int i = 0; i < path.size(); i++) {
            cout << path[i] + 1;
            if (i < path.size() - 1) {
                cout << " "; // Разделитель между вершинами
            }
        }
        cout << endl;
    }
    // Если start == end, то путь имеет длину 0, и мы выводим только длину
    
    return 0;
}

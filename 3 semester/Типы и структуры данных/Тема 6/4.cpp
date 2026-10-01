#include <iostream>
#include <vector>
using namespace std;

// Функция обхода графа в глубину (Depth-First Search)
// v - текущая вершина для посещения
// graph - матрица смежности графа
// visited - массив посещенных вершин
void dfs(int v, vector<vector<int>>& graph, vector<bool>& visited) {
    visited[v] = true; // Помечаем текущую вершину как посещенную
    
    // Проходим по всем вершинам графа
    for (int i = 0; i < graph.size(); i++) {
        // Если существует ребро из v в i (graph[v][i] == 1)
        // и вершина i еще не посещена
        if (graph[v][i] == 1 && !visited[i]) {
            dfs(i, graph, visited); // Рекурсивно посещаем вершину i
        }
    }
}

int main() {
    int n, s; // n - количество вершин, s - стартовая вершина
    cin >> n >> s;
    
    // Переводим в 0-индексацию для удобства работы с массивами
    s--;
    
    // Создаем матрицу смежности n x n для хранения графа
    // graph[i][j] = 1, если есть ребро из i в j, иначе 0
    vector<vector<int>> graph(n, vector<int>(n));
    
    // Чтение матрицы смежности из входных данных
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }
    
    // Массив для отслеживания посещенных вершин
    // visited[i] = true, если вершина i была посещена
    vector<bool> visited(n, false);
    
    // Запускаем обход в глубину из стартовой вершины s
    dfs(s, graph, visited);
    
    // Считаем количество посещенных вершин
    int count = 0;
    for (bool v : visited) {
        if (v) count++;
    }
    
    // Выводим результат - количество вершин, достижимых из стартовой
    cout << count << endl;
    
    return 0;
}

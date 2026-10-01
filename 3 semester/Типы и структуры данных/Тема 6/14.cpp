#include <iostream>
#include <vector>
using namespace std;

vector<int> graph;
vector<bool> visited;

void dfs(int v) {
    visited[v] = true;
    if (!visited[graph[v]]) {
        dfs(graph[v]);
    }
}

int main() {
    int n;
    cin >> n;
    
    graph.resize(n + 1);
    visited.resize(n + 1, false);
    
    // Чтение данных: ключ от i-й копилки лежит в graph[i]
    for (int i = 1; i <= n; i++) {
        cin >> graph[i];
    }
    
    // Ищем количество циклов в графе
    int cycles = 0;
    for (int i = 1; i <= n; i++) {
        if (!visited[i]) {
            // Запускаем DFS для каждой непосещенной вершины
            dfs(i);
            cycles++;
        }
    }
    
    // Если весь граф - один цикл, нужно разбить 1 копилку
    // Иначе нужно разбить по одной копилке в каждом цикле
    cout << (cycles == 1 ? 1 : cycles) << endl;
    
    return 0;
}

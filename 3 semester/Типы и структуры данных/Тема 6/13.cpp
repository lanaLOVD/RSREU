#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    
    vector<int> color(n + 1, -1); // -1 не посещена, 0 и 1 - цвета
    vector<int> table1;
    
    // Проверка на двудольность (стр. 22 лекции)
    for (int i = 1; i <= n; i++) {
        if (color[i] == -1) {
            // BFS для раскраски
            queue<int> q;
            q.push(i);
            color[i] = 0;
            table1.push_back(i);
            
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                
                for (int v : graph[u]) {
                    if (color[v] == -1) {
                        color[v] = 1 - color[u]; // противоположный цвет
                        if (color[v] == 0) {
                            table1.push_back(v);
                        }
                        q.push(v);
                    } else if (color[v] == color[u]) {
                        // Нашли конфликт - граф не двудольный
                        cout << "NO" << endl;
                        return 0;
                    }
                }
            }
        }
    }
    
    // Вывод результата
    cout << "YES" << endl;
    for (int person : table1) {
        cout << person << " ";
    }
    cout << endl;
    
    return 0;
}

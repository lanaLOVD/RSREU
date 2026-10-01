#include <iostream>
#include <vector>
using namespace std;

vector<vector<bool>> visited;
vector<string> grid;
int m, n;

void dfs(int x, int y) {
    if (x < 0 || x >= m || y < 0 || y >= n) return;
    if (visited[x][y] || grid[x][y] == '.') return;
    
    visited[x][y] = true;
    
    // Проверяем всех 4 соседей
    dfs(x + 1, y);
    dfs(x - 1, y);
    dfs(x, y + 1);
    dfs(x, y - 1);
}

int main() {
    cin >> m >> n;
    grid.resize(m);
    visited.resize(m, vector<bool>(n, false));
    
    for (int i = 0; i < m; i++) {
        cin >> grid[i];
    }
    
    int components = 0;
    
    // Поиск компонент связности с помощью DFS (стр. 7-9 лекции)
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited[i][j] && grid[i][j] == '#') {
                components++;
                dfs(i, j);
            }
        }
    }
    
    cout << components << endl;
    
    return 0;
}

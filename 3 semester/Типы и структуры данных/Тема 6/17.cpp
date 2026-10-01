#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

struct State {
    int x, y, moves;
};

int main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int>> maze(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> maze[i][j];
        }
    }
    
    // BFS для поиска минимального количества наклонов
    vector<vector<int>> dist(n, vector<int>(m, INT_MAX));
    queue<State> q;
    
    // Начальная позиция - левый верхний угол
    dist[0][0] = 0;
    q.push({0, 0, 0});
    
    int min_moves = INT_MAX;
    
    while (!q.empty()) {
        State current = q.front();
        q.pop();
        
        // Если уже нашли путь не лучше текущего, пропускаем
        if (current.moves >= min_moves) continue;
        
        // 4 направления: влево, вправо, вверх, вниз
        int dx[] = {0, 0, -1, 1};
        int dy[] = {-1, 1, 0, 0};
        
        for (int dir = 0; dir < 4; dir++) {
            int x = current.x;
            int y = current.y;
            
            // Двигаемся в выбранном направлении до препятствия или края
            while (true) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                
                // Проверяем границы
                if (nx < 0 || nx >= n || ny < 0 || ny >= m) break;
                
                // Если наткнулись на препятствие, останавливаемся
                if (maze[nx][ny] == 1) break;
                
                // Если нашли отверстие, обновляем минимальное количество ходов
                if (maze[nx][ny] == 2) {
                    min_moves = min(min_moves, current.moves + 1);
                    break;
                }
                
                x = nx;
                y = ny;
            }
            
            // Если сдвинулись с места и не нашли выход
            if ((x != current.x || y != current.y) && maze[x][y] != 2) {
                if (current.moves + 1 < dist[x][y]) {
                    dist[x][y] = current.moves + 1;
                    q.push({x, y, current.moves + 1});
                }
            }
        }
    }
    
    cout << min_moves << endl;
    
    return 0;
}

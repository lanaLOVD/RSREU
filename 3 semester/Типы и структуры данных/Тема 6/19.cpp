#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Возможные ходы коня (8 направлений)
const int dx[] = {2, 2, 1, 1, -1, -1, -2, -2};
const int dy[] = {1, -1, 2, -2, 2, -2, 1, -1};

struct State {
    int x1, y1, x2, y2, moves;
};

int main() {
    string pos1, pos2;
    cin >> pos1 >> pos2;
    
    // Преобразуем координаты в числовые (0-7)
    int x1 = pos1[0] - 'a';
    int y1 = pos1[1] - '1';
    int x2 = pos2[0] - 'a';
    int y2 = pos2[1] - '1';
    
    // BFS для поиска минимального количества ходов
    vector<vector<vector<vector<int>>>> dist(8,
        vector<vector<vector<int>>>(8,
            vector<vector<int>>(8,
                vector<int>(8, -1))));
    
    queue<State> q;
    
    // Начальное состояние
    dist[x1][y1][x2][y2] = 0;
    q.push({x1, y1, x2, y2, 0});
    
    int min_moves = -1;
    
    while (!q.empty()) {
        State current = q.front();
        q.pop();
        
        // Если уже встретились
        if (current.x1 == current.x2 && current.y1 == current.y2) {
            min_moves = current.moves;
            break;
        }
        
        // Ходы первого коня
        for (int i = 0; i < 8; i++) {
            int nx1 = current.x1 + dx[i];
            int ny1 = current.y1 + dy[i];
            
            if (nx1 < 0 || nx1 >= 8 || ny1 < 0 || ny1 >= 8) continue;
            
            // Ходы второго коня
            for (int j = 0; j < 8; j++) {
                int nx2 = current.x2 + dx[j];
                int ny2 = current.y2 + dy[j];
                
                if (nx2 < 0 || nx2 >= 8 || ny2 < 0 || ny2 >= 8) continue;
                
                // Если состояние еще не посещалось
                if (dist[nx1][ny1][nx2][ny2] == -1) {
                    dist[nx1][ny1][nx2][ny2] = current.moves + 1;
                    q.push({nx1, ny1, nx2, ny2, current.moves + 1});
                }
            }
        }
    }
    
    cout << min_moves << endl;
    
    return 0;
}

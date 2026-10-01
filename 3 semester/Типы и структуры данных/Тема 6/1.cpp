#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    vector<vector<int>> a(n, vector<int>(n));
    
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
        
    for (int i = 0; i < n; i++) {
        // Проверка главной диагонали
        if (a[i][i] != 0) {
            cout << "NO" << endl;  // Нашли петлю
            return 0;
        }
        
        // Проверка симметричности матрицы (должна быть симметрична)
        for (int j = i + 1; j < n; j++) {
            if (a[i][j] != a[j][i]) {
                cout << "NO" << endl;  // Несимметрична
                return 0;
            }
        }
    }
    
    cout << "YES" << endl;  // Граф является неориентированным без петель
    return 0;
}


#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double C;  // Целевое значение: x² + √x = C
    cin >> C;
    
    double left = 0.0;    // Нижняя граница
    double right = C;     // Верхняя граница ( x² ≤ C, значит x ≤ √C ≤ C)
    
    // Бинарный поиск с фиксированным числом итераций
    for (int i = 0; i < 100; i++) {
        double mid = (left + right) / 2.0;
        
        double value = mid * mid + sqrt(mid);
        
        if (value < C) {
            // Сдвигаем левую границу вправо
            left = mid;
        } else {
            // Сдвигаем правую границу влево
            right = mid;
        }
    }
    
    
    cout << fixed << setprecision(10) << left << endl;
    
    return 0;
}

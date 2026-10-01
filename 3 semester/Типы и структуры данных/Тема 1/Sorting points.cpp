#include <iostream>
#include <vector>
#include <algorithm>  // для sort
#include <cmath>      // для sqrt
using namespace std;

// Класс Point для представления точки в 2D-пространстве
class Point {
public:
    int x, y;  // Координаты точки

    // Конструктор класса Point
    Point(int x_, int y_) {
        x = x_;
        y = y_;
    }

    // Метод для вычисления расстояния от начала координат (0,0)
    double dist() const {
        return sqrt(x * x + y * y);
    }

    // Перегрузка оператора вывода для удобного отображения точки
    friend ostream& operator<<(ostream& out, const Point& p) {
        out << p.x << " " << p.y;
        return out;
    }
};

int main() {
    int n;
    cin >> n;   // Читаем количество точек

    vector<Point> points;  // Вектор для хранения точек
    
    // Чтение координат точек из входного потока
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        points.push_back(Point(x, y));  // Создаем и добавляем точку в вектор
    }

    // Сортируем точки по расстоянию до начала координат с помощью лямбда-функции
    sort(points.begin(), points.end(), [](const Point& a, const Point& b) {
        return a.dist() < b.dist();  // Критерий сравнения: расстояние a < расстояния b
    });

    // Выводим отсортированные точки
    for (auto& p : points) {
        cout << p << endl;  // Используем перегруженный оператор <<
    }

    return 0;
}

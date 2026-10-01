#include <stdio.h>
#include <math.h>
#include <float.h>

// Структура для точки
typedef struct {
    double x, y;
} Point;

// Структура для круга
typedef struct {
    Point center;
    double radius;
} Circle;

// Структура для прямоугольника
typedef struct {
    double x, y, width, height;
} Rectangle;

// 1. Создание круга
Circle createCircle(double x, double y, double radius) {
    Circle c;
    c.center.x = x;
    c.center.y = y;
    c.radius = radius > 0 ? radius : 0; // радиус не может быть отрицательным
    return c;
}

// 2. Проверка попадания точки в круг
int isPointInCircle(Circle c, Point p) {
    double dx = p.x - c.center.x;
    double dy = p.y - c.center.y;
    return (dx * dx + dy * dy) <= (c.radius * c.radius);
}

// 3. Проверка пересечения двух кругов
int doCirclesIntersect(Circle c1, Circle c2) {
    double dx = c1.center.x - c2.center.x;
    double dy = c1.center.y - c2.center.y;
    double distance = sqrt(dx * dx + dy * dy);
    return distance <= (c1.radius + c2.radius);
}

// 4. Проверка пересечения круга с прямоугольной областью
int doesCircleIntersectRectangle(Circle c, Rectangle r) {
    // Находим ближайшую точку прямоугольника к центру круга
    double closestX, closestY;
    
    if (c.center.x < r.x) {
        closestX = r.x;
    } else if (c.center.x > r.x + r.width) {
        closestX = r.x + r.width;
    } else {
        closestX = c.center.x;
    }
    
    if (c.center.y < r.y) {
        closestY = r.y;
    } else if (c.center.y > r.y + r.height) {
        closestY = r.y + r.height;
    } else {
        closestY = c.center.y;
    }
    
    // Проверяем расстояние от центра круга до ближайшей точки
    double dx = c.center.x - closestX;
    double dy = c.center.y - closestY;
    return (dx * dx + dy * dy) <= (c.radius * c.radius);
}

// 5. Площадь пересечения двух кругов (приближенно)
double intersectionArea(Circle c1, Circle c2) {
    double dx = c1.center.x - c2.center.x;
    double dy = c1.center.y - c2.center.y;
    double d = sqrt(dx * dx + dy * dy);
    
    // Круги не пересекаются
    if (d >= c1.radius + c2.radius) {
        return 0.0;
    }
    
    // Один круг полностью внутри другого
    if (d <= fabs(c1.radius - c2.radius)) {
        double r = fmin(c1.radius, c2.radius);
        return M_PI * r * r;
    }
    
    // Частичное пересечение
    double r1 = c1.radius;
    double r2 = c2.radius;
    
    double part1 = r1 * r1 * acos((d * d + r1 * r1 - r2 * r2) / (2 * d * r1));
    double part2 = r2 * r2 * acos((d * d + r2 * r2 - r1 * r1) / (2 * d * r2));
    double part3 = 0.5 * sqrt((-d + r1 + r2) * (d + r1 - r2) * (d - r1 + r2) * (d + r1 + r2));
    
    return part1 + part2 - part3;
}

// 6. Круг, описанный вокруг треугольника
Circle circumscribedCircle(Point p1, Point p2, Point p3) {
    Circle result;
    
    // Проверка на коллинеарность
    double area = fabs((p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)) / 2.0);
    if (area < 1e-9) {
        // Точки коллинеарны, возвращаем круг с радиусом 0
        result.center.x = p1.x;
        result.center.y = p1.y;
        result.radius = 0;
        return result;
    }
    
    // Вычисление центра описанной окружности
    double d = 2 * (p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y));
    
    double ux = ((p1.x * p1.x + p1.y * p1.y) * (p2.y - p3.y) +
                 (p2.x * p2.x + p2.y * p2.y) * (p3.y - p1.y) +
                 (p3.x * p3.x + p3.y * p3.y) * (p1.y - p2.y)) / d;
    
    double uy = ((p1.x * p1.x + p1.y * p1.y) * (p3.x - p2.x) +
                 (p2.x * p2.x + p2.y * p2.y) * (p1.x - p3.x) +
                 (p3.x * p3.x + p3.y * p3.y) * (p2.x - p1.x)) / d;
    
    result.center.x = ux;
    result.center.y = uy;
    
    // Радиус - расстояние от центра до любой вершины
    double dx = p1.x - ux;
    double dy = p1.y - uy;
    result.radius = sqrt(dx * dx + dy * dy);
    
    return result;
}

// 7. Минимальный круг, содержащий все круги из массива
Circle minEnclosingCircle(Circle circles[], int n) {
    if (n <= 0) {
        return createCircle(0, 0, 0);
    }
    
    // Находим границы всех кругов
    double minX = circles[0].center.x - circles[0].radius;
    double maxX = circles[0].center.x + circles[0].radius;
    double minY = circles[0].center.y - circles[0].radius;
    double maxY = circles[0].center.y + circles[0].radius;
    
    for (int i = 1; i < n; i++) {
        double left = circles[i].center.x - circles[i].radius;
        double right = circles[i].center.x + circles[i].radius;
        double bottom = circles[i].center.y - circles[i].radius;
        double top = circles[i].center.y + circles[i].radius;
        
        if (left < minX) minX = left;
        if (right > maxX) maxX = right;
        if (bottom < minY) minY = bottom;
        if (top > maxY) maxY = top;
    }
    
    // Центр - середина прямоугольника, содержащего все круги
    double centerX = (minX + maxX) / 2;
    double centerY = (minY + maxY) / 2;
    
    // Радиус - максимальное расстояние от центра до границы любого круга
    double maxRadius = 0;
    for (int i = 0; i < n; i++) {
        double dx = circles[i].center.x - centerX;
        double dy = circles[i].center.y - centerY;
        double distance = sqrt(dx * dx + dy * dy) + circles[i].radius;
        
        if (distance > maxRadius) {
            maxRadius = distance;
        }
    }
    
    return createCircle(centerX, centerY, maxRadius);
}

// 8. Вывод круга в консоль
void printCircle(Circle c) {
    printf("(%.2f, %.2f) [%.2f]\n", c.center.x, c.center.y, c.radius);
}

// Вспомогательная функция для ввода точки
Point inputPoint(const char* prompt) {
    Point p;
    printf("%s", prompt);
    scanf("%lf %lf", &p.x, &p.y);
    return p;
}

// Вспомогательная функция для ввода круга
Circle inputCircle(const char* prompt) {
    printf("%s", prompt);
    double x, y, r;
    scanf("%lf %lf %lf", &x, &y, &r);
    return createCircle(x, y, r);
}

// Вспомогательная функция для ввода прямоугольника
Rectangle inputRectangle(const char* prompt) {
    Rectangle r;
    printf("%s", prompt);
    scanf("%lf %lf %lf %lf", &r.x, &r.y, &r.width, &r.height);
    return r;
}

// Главное меню
int main() {
    int choice;
    
    do {
        printf("\n=== Меню операций с кругом ===\n");
        printf("1. Создание круга\n");
        printf("2. Проверка попадания точки в круг\n");
        printf("3. Проверка пересечения двух кругов\n");
        printf("4. Проверка пересечения круга с прямоугольной областью\n");
        printf("5. Расчет площади пересечения двух кругов\n");
        printf("6. Круг, описанный вокруг треугольника\n");
        printf("7. Минимальный круг, содержащий массив кругов\n");
        printf("8. Вывод круга в консоль\n");
        printf("0. Выход\n");
        printf("Выберите операцию: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1: {
                Circle c = inputCircle("Введите координаты центра и радиус (x y r): ");
                printf("Создан круг: ");
                printCircle(c);
                break;
            }
            
            case 2: {
                Circle c = inputCircle("Введите круг (x y r): ");
                Point p = inputPoint("Введите точку (x y): ");
                if (isPointInCircle(c, p)) {
                    printf("Точка находится внутри круга.\n");
                } else {
                    printf("Точка находится вне круга.\n");
                }
                break;
            }
            
            case 3: {
                Circle c1 = inputCircle("Введите первый круг (x y r): ");
                Circle c2 = inputCircle("Введите второй круг (x y r): ");
                if (doCirclesIntersect(c1, c2)) {
                    printf("Круги пересекаются.\n");
                } else {
                    printf("Круги не пересекаются.\n");
                }
                break;
            }
            
            case 4: {
                Circle c = inputCircle("Введите круг (x y r): ");
                Rectangle r = inputRectangle("Введите прямоугольник (x y width height): ");
                if (doesCircleIntersectRectangle(c, r)) {
                    printf("Круг пересекается с прямоугольником.\n");
                } else {
                    printf("Круг не пересекается с прямоугольником.\n");
                }
                break;
            }
            
            case 5: {
                Circle c1 = inputCircle("Введите первый круг (x y r): ");
                Circle c2 = inputCircle("Введите второй круг (x y r): ");
                double area = intersectionArea(c1, c2);
                printf("Площадь пересечения: %.4f\n", area);
                break;
            }
            
            case 6: {
                Point p1 = inputPoint("Введите первую точку треугольника (x y): ");
                Point p2 = inputPoint("Введите вторую точку треугольника (x y): ");
                Point p3 = inputPoint("Введите третью точку треугольника (x y): ");
                Circle c = circumscribedCircle(p1, p2, p3);
                printf("Описанный круг: ");
                printCircle(c);
                break;
            }
            
            case 7: {
                int n;
                printf("Введите количество кругов в массиве: ");
                scanf("%d", &n);
                
                if (n > 0) {
                    Circle circles[n];
                    for (int i = 0; i < n; i++) {
                        printf("Круг %d: ", i + 1);
                        circles[i] = inputCircle("");
                    }
                    
                    Circle enclosing = minEnclosingCircle(circles, n);
                    printf("Минимальный круг, содержащий все круги: ");
                    printCircle(enclosing);
                } else {
                    printf("Массив пуст.\n");
                }
                break;
            }
            
            case 8: {
                Circle c = inputCircle("Введите круг (x y r): ");
                printf("Круг: ");
                printCircle(c);
                break;
            }
            
            case 0:
                printf("Выход из программы.\n");
                break;
                
            default:
                printf("Неверный выбор. Попробуйте снова.\n");
        }
    } while (choice != 0);
    
    return 0;
}

// Файл: main.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Vector3d.h"

using namespace std;

// ====================== ВСПОМОГАТЕЛЬНЫЕ ФУНКЦИИ ======================
Vector3d inputVectorManually() {
    double x, y, z;
    cout << "Введите x y z → ";
    cin >> x >> y >> z;
    return createVector3d(x, y, z);
}

Vector3d generateRandomVector(double min = -10.0, double max = 10.0) {
    double x = min + (max - min) * (rand() / (double)RAND_MAX);
    double y = min + (max - min) * (rand() / (double)RAND_MAX);
    double z = min + (max - min) * (rand() / (double)RAND_MAX);
    return createVector3d(x, y, z);
}

// ====================== ГЛАВНАЯ ПРОГРАММА ======================
int main() {
    setlocale(LC_ALL, "Russian");
    srand(static_cast<unsigned>(time(nullptr)));

    // === КРАСИВЫЕ ВЕКТОРЫ ПО УМОЛЧАНИЮ ===
    const Vector3d DEFAULT_VECTOR = createVector3d(3.0, 4.0, 12.0);   // длина = 13
    const Vector3d EXAMPLE_A      = createVector3d(1.0, 2.0, 3.0);
    const Vector3d EXAMPLE_B      = createVector3d(4.0, -5.0, 6.0);

    int choice, subchoice;
    Vector3d v1, v2, result;

    do {
        cout << "\n=== Трёхмерные векторы ===\n";
        cout << "1. Создать вектор\n";
        cout << "2. Сложение двух векторов\n";
        cout << "3. Вычитание двух векторов\n";
        cout << "4. Угол между двумя векторами\n";
        cout << "5. Нормализовать вектор\n";
        cout << "6. Векторное произведение\n";
        cout << "7. Проекция одного вектора на другой\n";
        cout << "0. Выход\n";
        cout << "→ ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
            // ====================== 1. СОЗДАНИЕ ВЕКТОРА ======================
            case 1: {
                cout << "\n=== Создание вектора ===\n";
                cout << "  1 — ввести вручную\n";
                cout << "  2 — сгенерировать случайно\n";
                cout << "  3 — по умолчанию (3, 4, 12)\n";
                cout << "  → ";
                cin >> subchoice;

                if (subchoice == 1)      v1 = inputVectorManually();
                else if (subchoice == 2) v1 = generateRandomVector();
                else if (subchoice == 3) v1 = DEFAULT_VECTOR;
                else {
                    cout << "Неверный выбор!\n";
                    break;
                }

                cout << "\nСоздан вектор: ";
                printVector3d(v1);
                break;
            }

            // ====================== ОПЕРАЦИИ С ДВУМЯ ВЕКТОРАМИ ======================
            case 2: case 3: case 4: case 6: case 7: {
                cout << "\n=== Первый вектор A ===\n";
                cout << "  1 — вручную     2 — случайно     3 — пример (1,2,3)\n  → ";
                cin >> subchoice;
                v1 = (subchoice == 1) ? inputVectorManually() :
                     (subchoice == 2) ? generateRandomVector() : EXAMPLE_A;

                cout << "=== Второй вектор B ===\n";
                cout << "  1 — вручную     2 — случайно     3 — пример (4,-5,6)\n  → ";
                cin >> subchoice;
                v2 = (subchoice == 1) ? inputVectorManually() :
                     (subchoice == 2) ? generateRandomVector() : EXAMPLE_B;

                cout << "\n  A: "; printVector3d(v1);
                cout << "  B: "; printVector3d(v2);

                if (choice == 2) {
                    result = add(v1, v2);
                    cout << "A + B  = ";
                }
                else if (choice == 3) {
                    result = subtract(v1, v2);
                    cout << "A − B  = ";
                }
                else if (choice == 4) {
                    double ang = angleBetween(v1, v2);
                    cout << "Угол между A и B = " << ang << " градусов\n";
                    continue;
                }
                else if (choice == 6) {
                    result = cross(v1, v2);
                    cout << "A × B  = ";
                }
                else if (choice == 7) {
                    result = project(v1, v2);
                    cout << "Проекция A на B = ";
                }
                printVector3d(result);
                break;
            }

            // ====================== 5. НОРМАЛИЗАЦИЯ ======================
            case 5: {
                cout << "\n=== Вектор для нормализации ===\n";
                cout << "  1 — вручную     2 — случайно     3 — по умолчанию (3,4,12)\n  → ";
                cin >> subchoice;

                v1 = (subchoice == 1) ? inputVectorManually() :
                     (subchoice == 2) ? generateRandomVector() : DEFAULT_VECTOR;

                cout << "\nИсходный:        "; printVector3d(v1);
                result = normalize(v1);
                cout << "Нормализованный: ";
                printVector3d(result);
                break;
            }

            default:
                cout << "Неверный пункт меню!\n";
        }
    } while (true);

    cout << "\nПрограмма завершена. До свидания!\n";
    return 0;
}

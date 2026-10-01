#include "list.h"
#include <iostream>
#include <string>

using namespace std;

int main() {
    cout << "=== Лабораторная работа №5 ===\n";
    cout << "Вариант 17 — Ограниченный односвязный список\n\n";

    int choice;
    do {
        cout << "\nВыберите тип для тестирования:\n";
        cout << "1. int \n";//(MaxVal = 10)
        cout << "2. float \n";//(MaxVal = 5.0)
        cout << "3. const char* \n";//(MaxVal = 5 символов)
        cout << "4. Vec2 \n";//(MaxVal = 10 по длине)
        cout << "0. Выход\n";
        cout << "Ваш выбор: ";
        cin >> choice;

        if (choice == 0) break;

        switch (choice) {
            case 1: { // int
                cout << "\nТестирование типа int\n";
                BoundedSinglyLinkedList<int, 10> list;
                int val, pos;

                cout << "Введите 4 целых числа (через пробел): ";
                for (int i = 0; i < 4; ++i) {
                    cin >> val;
                    list + val;                    // добавление в начало через +
                }
                cout << "Список после добавления: " << list << "\n";

                cout << "Введите позицию для вставки и значение: ";
                cin >> pos >> val;
                list.insert(val, pos);
                cout << "После insert: " << list << "\n";
                break;
            }

            case 2: { // float
                cout << "\nТестирование типа float\n";
                BoundedSinglyLinkedList<float, 5> list;
                float val;

                cout << "Введите 3 вещественных числа: ";
                for (int i = 0; i < 3; ++i) {
                    cin >> val;
                    list + val;
                }
                cout << "Список: " << list << "\n";
                break;
            }

            case 3: { // const char*
                cout << "\nТестирование типа const char*\n";
                BoundedSinglyLinkedList<const char*, 5> list;
                string str;

                cout << "Введите 3 строки (каждая не длиннее 5 символов):\n";
                for (int i = 0; i < 3; ++i) {
                    cin >> str;
                    list + str.c_str();           // добавляем как const char*
                }
                cout << "Список: " << list << "\n";

                cout << "Введите строку для удаления: ";
                cin >> str;
                list - str.c_str();
                cout << "После удаления: " << list << "\n";
                break;
            }

            case 4: { // Vec2
                cout << "\nТестирование типа Vec2\n";
                BoundedSinglyLinkedList<Vec2, 10> list;
                float x, y;

                cout << "Введите 2 вектора (x y для каждого):\n";
                for (int i = 0; i < 2; ++i) {
                    cin >> x >> y;
                    list + Vec2{x, y};
                }
                cout << "Список: " << list << "\n";

                cout << "Введите индекс для доступа: ";
                int idx;
                cin >> idx;
                if (idx >= 0 && idx < (int)list.getLength()) {
                    Vec2 v = list[idx];
                    cout << "Элемент [" << idx << "]: (" << v.x << ", " << v.y << ")\n";
                }
                break;
            }

            default:
                cout << "Неверный выбор!\n";
        }

        cout << "\nНажмите Enter для продолжения...";
        cin.ignore();
        cin.get();

    } while (choice != 0);

    cout << "\nТестирование завершено\n";
    return 0;
}

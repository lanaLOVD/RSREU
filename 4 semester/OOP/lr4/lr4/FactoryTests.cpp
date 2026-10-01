#include "FactoryTests.h"
#include "Factory.h"
#include "Worker.h"
#include "Engineer.h"
#include "ShopManager.h"
#include "Storekeeper.h"
#include "Object.h"
#include <iostream>

using namespace std;

static int passed = 0;
static int failed = 0;

void check(bool condition) {
    if (condition) {
        cout << "Тест пройден\n\n";
        passed++;
    } else {
        cout << "Тест провален\n\n";
        failed++;
    }
}

// Тест 1: Создание иерархии и расчёт зарплат
void testHierarchyAndSalary() {
    cout << "Тест 1: Иерархия сотрудников и расчёт зарплат\n";

    Factory factory("Радиозавод");

    // Создаём рабочих
    Worker* w1 = new Worker("Иванов Иван Иванович", 35);
    w1->addDetail("Корпус двигателя", 100, 115);
    w1->addDetail("Шестерня", 80, 85);

    Worker* w2 = new Worker("Петров Пётр Петрович", 29);
    w2->addDetail("Вал", 120, 110);
    w2->addDetail("Кронштейн", 50, 60);

    Worker* w3 = new Worker("Сидорова Анна Сергеевна", 27);
    w3->addDetail("Поршень", 200, 210);

    // Создаём инженера
    Engineer* eng1 = new Engineer("Кузнецов Сергей Викторович", 45);
    eng1->addSubordinate(w1);
    eng1->addSubordinate(w2);

    Engineer* eng2 = new Engineer("Смирнова Ольга Александровна", 38);
    eng2->addSubordinate(w3);

    // Начальник цеха
    ShopManager* manager = new ShopManager("Васильев Дмитрий Николаевич", 52);
    manager->addSubordinate(eng1);
    manager->addSubordinate(eng2);

    // Завхоз
    Storekeeper* storekeeper = new Storekeeper("Фёдоров Алексей Павлович", 48);
    storekeeper->addManagedShop(manager);
    manager->setStorekeeper(storekeeper);

    // Добавляем всех в завод
    factory.addEmployee(w1);
    factory.addEmployee(w2);
    factory.addEmployee(w3);
    factory.addEmployee(eng1);
    factory.addEmployee(eng2);
    factory.addEmployee(manager);
    factory.addEmployee(storekeeper);

    factory.printAll();

    double total = factory.totalSalary(10000.0);  // базовое значение = 10000
    cout << "Общая сумма зарплат на заводе (при base = 10000): "
         << total << " руб.\n\n";

    check(total > 0);
}

// Тест 2: Статистика по должностям
void testStatistics() {
    cout << "Тест 2: Статистика по количеству сотрудников\n";
    Factory factory("TestFactory");
    
    // Добавляем по одному сотруднику каждого типа
    factory.addEmployee(new Worker("Рабочий1", 30));
    factory.addEmployee(new Engineer("Инженер1", 40));
    factory.addEmployee(new ShopManager("НачЦеха1", 50));
    factory.addEmployee(new Storekeeper("Завхоз1", 45));

    factory.printStatistics();
    check(true);
}

// Тест 3: Полиморфизм через базовый класс
void testPolymorphism() {
    cout << "Тест 3: Полиморфизм (расчёт зарплаты через Person*)\n";

    Person* p1 = new Worker("Тестовый рабочий", 25);
    Person* p2 = new Engineer("Тестовый инженер", 40);

    cout << "Зарплата рабочего (base=10000): " << p1->calculateSalary(10000.0) << "\n";
    cout << "Зарплата инженера (base=25000): " << p2->calculateSalary(25000.0) << "\n";

    delete p1;
    delete p2;
    check(true);
}

// Тест 4: Статистика объектов Object
void testObjectStats() {
    cout << "Тест 4: Статистика объектов из класса Object\n";
    Object::printTotalInfo();
    check(true);
}

// Главная функция запуска тестов
void FactoryTests::runAllTests() {
    cout << "==========================================\n";
    cout << "   ЛАБОРАТОРНАЯ РАБОТА №4 — Вариант с Заводом\n";
    cout << "   Сущности: Рабочий, Инженер, Начальник цеха, Завхоз\n";
    cout << "==========================================\n\n";

    testHierarchyAndSalary();
    testStatistics();
    testPolymorphism();
    testObjectStats();

    cout << "====================\n";
    cout << "Пройдено тестов: " << passed << "\n";
    cout << "Провалено тестов: " << failed << "\n";
    cout << "====================\n\n";

    Object::printTotalInfo();
}

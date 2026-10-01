#include "Factory.h"
#include "Worker.h"
#include "Engineer.h"
#include "ShopManager.h"
#include "Storekeeper.h"
#include <iostream>
#include <limits>

Factory::Factory(const std::string& name) : factoryName(name) {
    addOp("Завод создан: " + name);
}

Factory::~Factory() {
    for (auto p : employees) delete p;
    addOp("Завод уничтожен");
}

void Factory::addEmployee(Person* p) {
    employees.push_back(p);
    addOp("Добавлен сотрудник: " + p->getFullName());
}

void Factory::printAll() const {
    std::cout << "\n=== Завод \"" << factoryName << "\" ===\n";
    for (auto p : employees) {
        p->printInfo();
        std::cout << "------------------------\n";
    }
}

double Factory::totalSalary(double baseValue) const {
    double sum = 0.0;
    for (auto p : employees) {
        sum += p->calculateSalary(baseValue);
    }
    return sum;
}

void Factory::printStatistics() const {
    int w=0, e=0, m=0, s=0;
    for (auto p : employees) {
        if (dynamic_cast<Worker*>(p)) w++;
        else if (dynamic_cast<Engineer*>(p)) e++;
        else if (dynamic_cast<ShopManager*>(p)) m++;
        else if (dynamic_cast<Storekeeper*>(p)) s++;
    }
    std::cout << "Статистика:\n";
    std::cout << "Рабочие: " << w << "\nИнженеры: " << e
              << "\nНачальники цехов: " << m << "\nЗавхозы: " << s << "\n\n";
}

void Factory::printMinMaxSalary(double baseValue) const {
    // можно реализовать, если нужно — сейчас просто заглушка
    std::cout << "Минимальная и максимальная зарплата по должностям (при base = "
              << baseValue << "):\n";
    // реализация по желанию
}

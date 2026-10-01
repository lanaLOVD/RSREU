// Engineer.cpp
#include "Engineer.h"
#include <iostream>

Engineer::Engineer(const std::string& name, int age) : Person(name, age) {
    addOp("Инженер создан");
}

Engineer::~Engineer() {
    addOp("Инженер уничтожен");
}

void Engineer::addSubordinate(Worker* w) {
    subordinates.push_back(w);
    addOp("Добавлен подчинённый: " + w->getFullName());
}

double Engineer::getPerformance() const {
    if (subordinates.empty()) return 0.0;
    double sum = 0.0;
    for (auto w : subordinates) {
        sum += w->getPerformance();
    }
    return sum / subordinates.size();
}

double Engineer::calculateSalary(double baseValue) const {
    double perf = getPerformance();
    double salary = baseValue * perf;
    if (perf > 1.0) salary *= 1.10;   // +10% надбавка за перевыполнение
    return salary;
}

void Engineer::printInfo() const {
    std::cout << "Инженер: " << fullName << ", возраст " << age
              << ", средний коэф. подчинённых: " << getPerformance()
              << ", зарплата: " << calculateSalary(25000.0) << " руб.\n";
    printOp();
}

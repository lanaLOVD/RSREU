// Worker.cpp
#include "Worker.h"
#include <iostream>
#include <numeric>

Worker::Worker(const std::string& name, int age) : Person(name, age) {
    addOp("Рабочий создан");
}

void Worker::addDetail(const std::string& name, double norm, double actual) {
    details.emplace_back(name, norm, actual);
    addOp("Добавлена деталь: " + name);
}

double Worker::getPerformance() const {
    if (details.empty()) return 0.0;
    double sum = 0.0;
    for (const auto& d : details) {
        sum += d.getPerformance();
    }
    return sum / details.size();
}

double Worker::calculateSalary(double baseValue) const {
    return baseValue * getPerformance();
}

void Worker::printInfo() const {
    std::cout << "Рабочий: " << fullName << ", возраст " << age
              << ", коэффициент производительности: " << getPerformance()
              << ", зарплата: " << calculateSalary(10000.0) << " руб.\n";
    std::cout << "   Детали:\n";
    for (const auto& d : details) {
        std::cout << "     - " << d.name << ": норма " << d.norm
                  << ", факт " << d.actual
                  << " (коэф. " << d.getPerformance() << ")\n";
    }
    printOp();
}

#include "ShopManager.h"
#include "Storekeeper.h"   // теперь можно включить здесь
#include <iostream>

ShopManager::ShopManager(const std::string& name, int age) : Person(name, age), storekeeper(nullptr) {
    addOp("Начальник цеха создан");
}

ShopManager::~ShopManager() {
    addOp("Начальник цеха уничтожен");
}

void ShopManager::addSubordinate(Engineer* e) {
    subordinates.push_back(e);
    addOp("Добавлен инженер: " + e->getFullName());
}

void ShopManager::setStorekeeper(Storekeeper* sk) {
    storekeeper = sk;
    addOp("Закреплён завхоз: " + (sk ? sk->getFullName() : "nullptr"));
}

double ShopManager::calculateSalary(double baseValue) const {
    if (subordinates.empty()) return baseValue;

    double avgPerf = 0.0;
    for (auto eng : subordinates) {
        avgPerf += eng->getPerformance();
    }
    avgPerf /= subordinates.size();

    double premium = 0.0;
    if (avgPerf > 1.3)      premium = baseValue * 0.5;   // +50%
    else if (avgPerf > 1.1) premium = baseValue * 0.25;  // +25%

    return baseValue + premium;
}

void ShopManager::printInfo() const {
    std::cout << "Начальник цеха: " << fullName << " (" << age << " лет)\n";
    std::cout << "   Зарплата (base=60000): " << calculateSalary(60000.0) << " руб.\n";
    if (storekeeper)
        std::cout << "   Закреплённый завхоз: " << storekeeper->getFullName() << "\n";
    printOp();
}

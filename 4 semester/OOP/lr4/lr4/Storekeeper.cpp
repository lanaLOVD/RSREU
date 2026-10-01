#include "Storekeeper.h"
#include "ShopManager.h"   // теперь можно включить здесь
#include <iostream>

Storekeeper::Storekeeper(const std::string& name, int age) : Person(name, age) {
    addOp("Завхоз создан");
}

void Storekeeper::addManagedShop(ShopManager* sm) {
    managedShops.push_back(sm);
    addOp("Добавлен цех для снабжения: " + sm->getFullName());
}

double Storekeeper::calculateSalary(double baseValue) const {
    return baseValue * 1.6;  // +60%
}

void Storekeeper::printInfo() const {
    std::cout << "Завхоз: " << fullName << " (" << age << " лет)\n";
    std::cout << "   Зарплата (base=40000): " << calculateSalary(40000.0) << " руб.\n";
    if (!managedShops.empty()) {
        std::cout << "   Обслуживаемые цеха: ";
        for (auto sm : managedShops)
            std::cout << sm->getFullName() << " ";
        std::cout << "\n";
    }
    printOp();
}

#ifndef STOREKEEPER_H
#define STOREKEEPER_H

#include "Person.h"
#include <vector>
#include <string>

// Forward declaration — говорим, что такой класс существует
class ShopManager;

class Storekeeper : public Person {
private:
    std::vector<ShopManager*> managedShops;

public:
    Storekeeper(const std::string& name, int age);
    void addManagedShop(ShopManager* sm);
    double calculateSalary(double baseValue) const override;
    void printInfo() const override;
};

#endif

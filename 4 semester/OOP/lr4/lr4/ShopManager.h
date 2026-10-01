#ifndef SHOPMANAGER_H
#define SHOPMANAGER_H

#include "Person.h"
#include "Engineer.h"
#include <vector>
#include <string>

// Forward declaration
class Storekeeper;

class ShopManager : public Person {
private:
    std::vector<Engineer*> subordinates;
    Storekeeper* storekeeper;

public:
    ShopManager(const std::string& name, int age);
    ~ShopManager();

    void addSubordinate(Engineer* e);
    void setStorekeeper(Storekeeper* sk);
    double calculateSalary(double baseValue) const override;
    void printInfo() const override;
};

#endif

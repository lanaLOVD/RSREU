#ifndef FACTORY_H
#define FACTORY_H

#include "Person.h"
#include <vector>

class Factory : public Object {
private:
    std::string factoryName;
    std::vector<Person*> employees;

public:
    Factory(const std::string& name);
    ~Factory();

    void addEmployee(Person* p);
    void printAll() const;
    double totalSalary(double baseValue) const;

    // Статистика
    void printStatistics() const;
    void printMinMaxSalary(double baseValue) const;
};

#endif

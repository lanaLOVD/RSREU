// Engineer.h
#ifndef ENGINEER_H
#define ENGINEER_H

#include "Person.h"
#include "Worker.h"
#include <vector>

class Engineer : public Person {
private:
    std::vector<Worker*> subordinates;

public:
    Engineer(const std::string& name, int age);
    ~Engineer();

    void addSubordinate(Worker* w);
    double calculateSalary(double baseValue) const override;
    void printInfo() const override;
    double getPerformance() const;
};

#endif

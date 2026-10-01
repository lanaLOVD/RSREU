#ifndef PERSON_H
#define PERSON_H

#include "Object.h"
#include <string>

class Person : public Object {
protected:
    std::string fullName;
    int age;

public:
    Person(const std::string& name, int age);
    virtual ~Person();

    virtual double calculateSalary(double baseValue) const = 0;
    virtual void printInfo() const = 0;

    std::string getFullName() const;
    int getAge() const;
};

#endif

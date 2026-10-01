#include "Person.h"
#include <iostream>

Person::Person(const std::string& name, int age) : fullName(name), age(age) {
    addOp("Person создан: " + name);
}

Person::~Person() {
    addOp("Person уничтожен");
}

std::string Person::getFullName() const { return fullName; }
int Person::getAge() const { return age; }

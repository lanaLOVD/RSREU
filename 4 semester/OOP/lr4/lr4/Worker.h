// Worker.h
#ifndef WORKER_H
#define WORKER_H

#include "Person.h"
#include "Detail.h"
#include <vector>

class Worker : public Person {
private:
    std::vector<Detail> details;

public:
    Worker(const std::string& name, int age);

    void addDetail(const std::string& name, double norm, double actual);
    double calculateSalary(double baseValue) const override;
    void printInfo() const override;
    double getPerformance() const;
};

#endif

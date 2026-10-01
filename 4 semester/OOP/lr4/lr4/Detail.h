#ifndef DETAIL_H
#define DETAIL_H

#include <string>

struct Detail {
    std::string name;
    double norm;      // норма выработки
    double actual;    // фактическая выработка

    Detail(const std::string& n, double no, double ac);
    double getPerformance() const;   // фактическая / норма
};

#endif


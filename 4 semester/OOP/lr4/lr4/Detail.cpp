#include "Detail.h"

Detail::Detail(const std::string& n, double no, double ac)
    : name(n), norm(no), actual(ac) {}

double Detail::getPerformance() const {
    return (norm > 0) ? actual / norm : 0.0;
}

// Файл: Vector3d.cpp
#include "Vector3d.h"

Vector3d createVector3d(double x, double y, double z) {
    Vector3d v;
    v.x = x;
    v.y = y;
    v.z = z;
    v.norm = false;           // при создании считаем, что не нормализован
    return v;
}

Vector3d add(const Vector3d& a, const Vector3d& b) {
    Vector3d res;
    res.x = a.x + b.x;
    res.y = a.y + b.y;
    res.z = a.z + b.z;
    res.norm = false;         // сумма нормализованных векторов обычно уже не единичная
    return res;
}

Vector3d subtract(const Vector3d& a, const Vector3d& b) {
    Vector3d res;
    res.x = a.x - b.x;
    res.y = a.y - b.y;
    res.z = a.z - b.z;
    res.norm = false;
    return res;
}

double length(const Vector3d& v) {
    return std::sqrt(v.x*v.x + v.y*v.y + v.z*v.z);
}

double dot(const Vector3d& a, const Vector3d& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

double angleBetween(const Vector3d& a, const Vector3d& b) {
    double lenA = length(a);
    double lenB = length(b);

    if (lenA < 1e-9 || lenB < 1e-9) {
        return 0.0; // неопределённый случай — один из векторов нулевой
    }

    double cosTheta = dot(a, b) / (lenA * lenB);

    // Защита от ошибок округления
    if (cosTheta > 1.0)  cosTheta = 1.0;
    if (cosTheta < -1.0) cosTheta = -1.0;

    return std::acos(cosTheta) * 180.0 / M_PI;
}

Vector3d normalize(const Vector3d& v) {
    double len = length(v);
    Vector3d res = v;

    if (len < 1e-9) {
        // нулевой вектор — оставляем как есть, но помечаем нормализованным
        res.norm = true;
        return res;
    }

    res.x /= len;
    res.y /= len;
    res.z /= len;
    res.norm = true;

    return res;
}

Vector3d cross(const Vector3d& a, const Vector3d& b) {
    Vector3d res;
    res.x = a.y * b.z - a.z * b.y;
    res.y = a.z * b.x - a.x * b.z;
    res.z = a.x * b.y - a.y * b.x;
    res.norm = false;
    return res;
}

Vector3d project(const Vector3d& a, const Vector3d& b) {
    double lenB2 = dot(b, b);
    if (lenB2 < 1e-12) {
        // вектор b нулевой → проекция = 0
        return createVector3d(0, 0, 0);
    }

    double coeff = dot(a, b) / lenB2;

    Vector3d res;
    res.x = coeff * b.x;
    res.y = coeff * b.y;
    res.z = coeff * b.z;
    res.norm = false;

    return res;
}

void printVector3d(const Vector3d& v) {
    std::cout << "("
              << v.x << ", "
              << v.y << ", "
              << v.z << ")  ["
              << (v.norm ? "нормализован" : "не нормализован")
              << "]\n";
}

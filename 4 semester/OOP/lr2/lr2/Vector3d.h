//Файл: Vector3d.h
#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>

class Vector3d
{
private:
    double x;
    double y;
    double z;
    bool norm;

    double length() const;

public:
    // конструктор
    Vector3d(double x, double y, double z);

    // геттеры
    double getX() const;
    double getY() const;
    double getZ() const;
    bool isNormalized() const;

    // сеттеры
    void setX(double value);
    void setY(double value);
    void setZ(double value);

    // операции
    Vector3d add(const Vector3d& v) const;
    Vector3d subtract(const Vector3d& v) const;
    double angleBetween(const Vector3d& v) const;
    Vector3d normalize() const;
    Vector3d crossProduct(const Vector3d& v) const;
    Vector3d projection(const Vector3d& v) const;

    void print() const;
};

#endif

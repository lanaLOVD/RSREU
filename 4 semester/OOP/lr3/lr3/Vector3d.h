#ifndef VECTOR3D_H
#define VECTOR3D_H

#include "Object.h"
#include <iostream>

class Vector3d : public Object
{
private:
    double x;
    double y;
    double z;
    bool norm;

    double length() const;

public:
    Vector3d(double x = 0.0, double y = 0.0, double z = 0.0);
    Vector3d(const Vector3d& other);
    Vector3d& operator=(const Vector3d& other);

    double getX() const;
    double getY() const;
    double getZ() const;
    bool isNormalized() const;

    void setX(double value);
    void setY(double value);
    void setZ(double value);

    Vector3d operator+(const Vector3d& v) const;
    Vector3d operator-(const Vector3d& v) const;
    double operator*(const Vector3d& v) const;
    Vector3d operator^(const Vector3d& v) const;
    Vector3d operator*(double scalar) const;

    Vector3d normalize() const;
    Vector3d projection(const Vector3d& v) const;
    double angleBetween(const Vector3d& v) const;

    void print() const;

    static Vector3d random(double min = -10.0, double max = 10.0);
};

#endif

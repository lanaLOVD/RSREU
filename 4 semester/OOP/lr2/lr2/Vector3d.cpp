//Файл: Vector3d.cpp
#include "Vector3d.h"
#include <cmath>

Vector3d::Vector3d(double x, double y, double z)
{
    this->x = x;
    this->y = y;
    this->z = z;

    double len = sqrt(x*x + y*y + z*z);
    norm = (fabs(len - 1.0) < 1e-9);
}

double Vector3d::length() const
{
    return sqrt(x*x + y*y + z*z);
}

double Vector3d::getX() const { return x; }
double Vector3d::getY() const { return y; }
double Vector3d::getZ() const { return z; }
bool Vector3d::isNormalized() const { return norm; }

void Vector3d::setX(double value) { x = value; }
void Vector3d::setY(double value) { y = value; }
void Vector3d::setZ(double value) { z = value; }

Vector3d Vector3d::add(const Vector3d& v) const
{
    return Vector3d(x + v.x, y + v.y, z + v.z);
}

Vector3d Vector3d::subtract(const Vector3d& v) const
{
    return Vector3d(x - v.x, y - v.y, z - v.z);
}

double Vector3d::angleBetween(const Vector3d& v) const
{
    double dot = x*v.x + y*v.y + z*v.z;
    double len = length() * v.length();

    if(len == 0) return 0;

    return acos(dot / len);
}

Vector3d Vector3d::normalize() const
{
    double len = length();

    if(len == 0)
        return Vector3d(0,0,0);

    return Vector3d(x/len, y/len, z/len);
}

Vector3d Vector3d::crossProduct(const Vector3d& v) const
{
    return Vector3d(
        y*v.z - z*v.y,
        z*v.x - x*v.z,
        x*v.y - y*v.x
    );
}

Vector3d Vector3d::projection(const Vector3d& v) const
{
    double dot = x*v.x + y*v.y + z*v.z;
    double len = v.x*v.x + v.y*v.y + v.z*v.z;

    if(len == 0)
        return Vector3d(0,0,0);

    double k = dot / len;

    return Vector3d(
        k*v.x,
        k*v.y,
        k*v.z
    );
}

void Vector3d::print() const
{
    std::cout << "(" << x << "," << y << "," << z << ") ["
              << (norm ? "нормализован" : "не нормализован")
              << "]" << std::endl;
}

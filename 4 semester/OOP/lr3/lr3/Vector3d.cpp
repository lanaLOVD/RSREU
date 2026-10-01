#include "Vector3d.h"
#include <cmath>
#include <cstdlib>
#include <ctime>

Vector3d::Vector3d(double x, double y, double z) : Object(), x(x), y(y), z(z)
{
    double len = length();
    norm = (fabs(len - 1.0) < 1e-9);
    addOp("Vector3d создан с координатами (" +
          std::to_string(x) + ", " + std::to_string(y) + ", " + std::to_string(z) + ")");
}

Vector3d::Vector3d(const Vector3d& other) : Object(other),
    x(other.x), y(other.y), z(other.z), norm(other.norm)
{
    addOp("Vector3d создан конструктором копирования");
}

Vector3d& Vector3d::operator=(const Vector3d& other)
{
    if (this == &other) return *this;
    Object::operator=(other);
    x = other.x;
    y = other.y;
    z = other.z;
    norm = other.norm;
    addOp("Vector3d присвоен оператором =");
    return *this;
}

double Vector3d::length() const
{
    return sqrt(x*x + y*y + z*z);
}

double Vector3d::getX() const { return x; }
double Vector3d::getY() const { return y; }
double Vector3d::getZ() const { return z; }
bool Vector3d::isNormalized() const { return norm; }

void Vector3d::setX(double value) { x = value; norm = false; }
void Vector3d::setY(double value) { y = value; norm = false; }
void Vector3d::setZ(double value) { z = value; norm = false; }

Vector3d Vector3d::operator+(const Vector3d& v) const
{
    addOp("Выполнена операция +");
    return Vector3d(x + v.x, y + v.y, z + v.z);
}

Vector3d Vector3d::operator-(const Vector3d& v) const
{
    addOp("Выполнена операция -");
    return Vector3d(x - v.x, y - v.y, z - v.z);
}

double Vector3d::operator*(const Vector3d& v) const
{
    addOp("Выполнено скалярное произведение");
    return x*v.x + y*v.y + z*v.z;
}

Vector3d Vector3d::operator^(const Vector3d& v) const
{
    addOp("Выполнено векторное произведение");
    return Vector3d(
        y * v.z - z * v.y,
        z * v.x - x * v.z,
        x * v.y - y * v.x
    );
}

Vector3d Vector3d::operator*(double scalar) const
{
    addOp("Умножение на скаляр");
    return Vector3d(x*scalar, y*scalar, z*scalar);
}

Vector3d Vector3d::normalize() const
{
    addOp("Выполнена нормализация");
    double len = length();
    if (len == 0.0)
        return Vector3d(0, 0, 0);
    return Vector3d(x/len, y/len, z/len);
}

Vector3d Vector3d::projection(const Vector3d& v) const
{
    addOp("Выполнена проекция");
    double dot = *this * v;
    double len2 = v.getX()*v.getX() + v.getY()*v.getY() + v.getZ()*v.getZ();
    if (len2 == 0.0)
        return Vector3d(0, 0, 0);
    return v * (dot / len2);
}

double Vector3d::angleBetween(const Vector3d& v) const
{
    addOp("Вычислен угол между векторами");
    double dot = *this * v;
    double len = length() * v.length();
    if (len == 0.0) return 0.0;
    return acos(dot / len);
}

void Vector3d::print() const
{
    std::cout << "(" << x << ", " << y << ", " << z << ") ["
              << (norm ? "нормализован" : "не нормализован") << "]\n";
    printOp();
}

Vector3d Vector3d::random(double min, double max)
{
    static bool seeded = false;
    if (!seeded)
    {
        std::srand(static_cast<unsigned>(std::time(nullptr)));
        seeded = true;
    }
    double dx = min + (max - min) * std::rand() / RAND_MAX;
    double dy = min + (max - min) * std::rand() / RAND_MAX;
    double dz = min + (max - min) * std::rand() / RAND_MAX;
    return Vector3d(dx, dy, dz);
}

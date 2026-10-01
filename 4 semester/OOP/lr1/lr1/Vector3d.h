// Файл: Vector3d.h
#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include <cmath>

struct Vector3d {
    double x;
    double y;
    double z;
    bool norm;          // true = уже нормализован
};

// 1. Создание вектора
Vector3d createVector3d(double x, double y, double z);

// 2. Сложение векторов
Vector3d add(const Vector3d& a, const Vector3d& b);

// 3. Вычитание векторов
Vector3d subtract(const Vector3d& a, const Vector3d& b);

// 4. Угол между векторами (в градусах)
double angleBetween(const Vector3d& a, const Vector3d& b);

// 5. Нормализация вектора (возвращает новый нормализованный вектор)
Vector3d normalize(const Vector3d& v);

// 6. Векторное произведение (cross product)
Vector3d cross(const Vector3d& a, const Vector3d& b);

// 7. Проекция вектора a на вектор b
Vector3d project(const Vector3d& a, const Vector3d& b);

// 8. Красивый вывод вектора
void printVector3d(const Vector3d& v);

#endif

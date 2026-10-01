#include "Vector3dTests.h"
#include "Vector3d.h"
#include "Object.h"
#include <iostream>
#include <cmath>

using namespace std;

static int passed = 0;
static int failed = 0;

void check(bool condition)
{
    if (condition)
    {
        cout << "Тест пройден\n\n";
        passed++;
    }
    else
    {
        cout << "Тест провален\n\n";
        failed++;
    }
}

// ====================== Тесты операций ======================

void testAdd()
{
    cout << "Тест: operator+\n";
    Vector3d v1(1,2,3);
    Vector3d v2(2,3,4);
    Vector3d result = v1 + v2;
    cout << "Ожидается: (3,5,7)  Получено: ("
         << result.getX() << "," << result.getY() << "," << result.getZ() << ")\n";
    check(result.getX()==3 && result.getY()==5 && result.getZ()==7);
}

void testSubtract()
{
    cout << "Тест: operator-\n";
    Vector3d v1(5,5,5);
    Vector3d v2(2,1,3);
    Vector3d result = v1 - v2;
    cout << "Ожидается: (3,4,2)  Получено: ("
         << result.getX() << "," << result.getY() << "," << result.getZ() << ")\n";
    check(result.getX()==3 && result.getY()==4 && result.getZ()==2);
}

void testScalarMultiply()
{
    cout << "Тест: скалярное произведение (operator*)\n";
    Vector3d v1(1,2,3);
    Vector3d v2(4,5,6);
    double result = v1 * v2;
    cout << "Ожидается: 32  Получено: " << result << "\n";
    check(fabs(result - 32) < 0.001);
}

void testCrossProduct()
{
    cout << "Тест: векторное произведение (operator^)\n";
    Vector3d v1(1,0,0);
    Vector3d v2(0,1,0);
    Vector3d result = v1 ^ v2;
    cout << "Ожидается: (0,0,1)  Получено: ("
         << result.getX() << "," << result.getY() << "," << result.getZ() << ")\n";
    check(result.getZ() == 1);
}

void testNormalize()
{
    cout << "Тест: normalize()\n";
    Vector3d v(3,0,0);
    Vector3d result = v.normalize();
    cout << "Ожидается: (1,0,0)  Получено: ("
         << result.getX() << "," << result.getY() << "," << result.getZ() << ")\n";
    check(fabs(result.getX() - 1) < 0.001);
}

void testProjection()
{
    cout << "Тест: projection()\n";
    Vector3d v1(2,0,0);
    Vector3d v2(1,0,0);
    Vector3d result = v1.projection(v2);
    cout << "Ожидается: (2,0,0)  Получено: ("
         << result.getX() << "," << result.getY() << "," << result.getZ() << ")\n";
    check(result.getX() == 2);
}

void testAngleBetween()
{
    cout << "Тест: angleBetween()\n";
    Vector3d v1(1,0,0);
    Vector3d v2(0,1,0);
    double result = v1.angleBetween(v2);
    cout << "Ожидается ≈1.57  Получено: " << result << "\n";
    check(fabs(result - 1.5708) < 0.01);
}

// ====================== Тесты Object ======================

void testObjectStats()
{
    cout << "Тест: статистика объектов Object\n";
    int activeBefore = Object::getTotalActive();
    {
        Vector3d v(10,20,30);
        Object::printTotalInfo();
    }
    check(Object::getTotalActive() == activeBefore);
}

void testRandom()
{
    cout << "Тест: Vector3d::random()\n";
    Vector3d v = Vector3d::random(-5.0, 5.0);
    cout << "Сгенерирован вектор: (" << v.getX() << ", " << v.getY() << ", " << v.getZ() << ")\n";
    check(true); // проверяем, что не упал
}

void testCopyConstructor()
{
    cout << "Тест: конструктор копирования\n";
    Vector3d v1(10,20,30);
    Vector3d v2 = v1;
    check(v2.getX() == 10 && v2.getY() == 20 && v2.getZ() == 30);
}

void testAssignment()
{
    cout << "Тест: operator=\n";
    Vector3d v1(1,2,3);
    Vector3d v2(99,99,99);
    v2 = v1;
    check(v2.getX() == 1 && v2.getY() == 2 && v2.getZ() == 3);
}

void testChainAssignment()
{
    cout << "Тест: цепочка присваиваний a = b = c\n";
    Vector3d a(1,1,1), b, c;
    c = b = a;
    check(c.getX() == 1 && b.getX() == 1);
}

// ====================== Запуск всех тестов ======================

void Vector3dTests::runAllTests()
{
    cout << "=== Запуск тестов лабораторной работы №3 ===\n\n";

    testAdd();
    testSubtract();
    testScalarMultiply();
    testCrossProduct();
    testNormalize();
    testProjection();
    testAngleBetween();

    testObjectStats();
    testRandom();
    testCopyConstructor();
    testAssignment();
    testChainAssignment();

    cout << "====================\n";
    cout << "Пройдено тестов: " << passed << "\n";
    cout << "Провалено тестов: " << failed << "\n";
    cout << "====================\n\n";

    Object::printTotalInfo();
}

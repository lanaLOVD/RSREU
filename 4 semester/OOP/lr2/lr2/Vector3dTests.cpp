//Файл: Vector3dTests.cpp
#include "Vector3dTests.h"
#include "Vector3d.h"
#include <iostream>
#include <cmath>

using namespace std;

static int passed = 0;
static int failed = 0;

void check(bool condition)
{
    if(condition)
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

void testAdd()
{
    cout << "Тест: add()\n";

    // Arrange
    Vector3d v1(1,2,3);
    Vector3d v2(2,3,4);

    // Act
    Vector3d result = v1.add(v2);

    // Assert
    cout<<"Ожидается: (3,5,7)\n";
    cout<<"Получено: ("<<result.getX()<<","<<result.getY()<<","<<result.getZ()<<")\n";

    check(result.getX()==3 && result.getY()==5 && result.getZ()==7);
}

void testSubtract()
{
    cout<<"Тест: subtract()\n";

    Vector3d v1(5,5,5);
    Vector3d v2(2,1,3);

    Vector3d result = v1.subtract(v2);

    cout<<"Ожидается: (3,4,2)\n";
    cout<<"Получено: ("<<result.getX()<<","<<result.getY()<<","<<result.getZ()<<")\n";

    check(result.getX()==3 && result.getY()==4 && result.getZ()==2);
}

void testNormalize()
{
    cout<<"Тест: normalize()\n";

    Vector3d v(3,0,0);

    Vector3d result = v.normalize();

    cout<<"Ожидается: (1,0,0)\n";
    cout<<"Получено: ("<<result.getX()<<","<<result.getY()<<","<<result.getZ()<<")\n";

    check(fabs(result.getX()-1)<0.001);
}

void testCrossProduct()
{
    cout<<"Тест: crossProduct()\n";

    Vector3d v1(1,0,0);
    Vector3d v2(0,1,0);

    Vector3d result = v1.crossProduct(v2);

    cout<<"Ожидается: (0,0,1)\n";
    cout<<"Получено: ("<<result.getX()<<","<<result.getY()<<","<<result.getZ()<<")\n";

    check(result.getZ()==1);
}

void testProjection()
{
    cout<<"Тест: projection()\n";

    Vector3d v1(2,0,0);
    Vector3d v2(1,0,0);

    Vector3d result = v1.projection(v2);

    cout<<"Ожидается: (2,0,0)\n";
    cout<<"Получено: ("<<result.getX()<<","<<result.getY()<<","<<result.getZ()<<")\n";

    check(result.getX()==2);
}
void testAngleBetween()
{
    cout<<"Тест: angleBetween()\n";

    // Arrange
    Vector3d v1(1,0,0);
    Vector3d v2(0,1,0);

    // Act
    double result = v1.angleBetween(v2);

    // Assert
    cout<<"Ожидается: ~1.57\n";
    cout<<"Получено: "<<result<<"\n";

    check(fabs(result - 1.5708) < 0.01);
}

void testSetX()
{
    cout<<"Тест: setX()\n";

    // Arrange
    Vector3d v(1,2,3);

    // Act
    v.setX(10);

    // Assert
    cout<<"Ожидается X: 10\n";
    cout<<"Получено X: "<<v.getX()<<"\n";

    check(v.getX()==10);
}

void testSetY()
{
    cout<<"Тест: setY()\n";

    // Arrange
    Vector3d v(1,2,3);

    // Act
    v.setY(20);

    // Assert
    cout<<"Ожидается Y: 20\n";
    cout<<"Получено Y: "<<v.getY()<<"\n";

    check(v.getY()==20);
}

void testSetZ()
{
    cout<<"Тест: setZ()\n";

    // Arrange
    Vector3d v(1,2,3);

    // Act
    v.setZ(30);

    // Assert
    cout<<"Ожидается Z: 30\n";
    cout<<"Получено Z: "<<v.getZ()<<"\n";

    check(v.getZ()==30);
}

void testNormalizeAnother()
{
    cout<<"Тест: normalize() второй случай\n";

    // Arrange
    Vector3d v(0,5,0);

    // Act
    Vector3d result = v.normalize();

    // Assert
    cout<<"Ожидается: (0,1,0)\n";
    cout<<"Получено: ("<<result.getX()<<","<<result.getY()<<","<<result.getZ()<<")\n";

    check(fabs(result.getY()-1) < 0.001);
}
void Vector3dTests::runAllTests()
{
    testAdd();
    testSubtract();
    testNormalize();
    testCrossProduct();
    testProjection();

    testAngleBetween();
    testSetX();
    testSetY();
    testSetZ();
    testNormalizeAnother();

    cout<<"====================\n";
    cout<<"Пройдено: "<<passed<<"\n";
    cout<<"Провалено: "<<failed<<"\n";
}

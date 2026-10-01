#include "Object.h"
#include <iostream>

int Object::totalCreated = 0;
int Object::totalActive = 0;

Object::Object() : operations(nullptr), opCount(0), opCapacity(0)
{
    totalCreated++;
    totalActive++;
    addOp("Создан объект (базовый конструктор)");
}

Object::Object(const Object& other) : operations(nullptr), opCount(0), opCapacity(0)
{
    totalCreated++;
    totalActive++;
    addOp("Создан конструктором копирования");
    *this = other;
}

Object& Object::operator=(const Object& other)
{
    if (this == &other) return *this;

    clearOp();

    for (int i = 0; i < other.opCount; ++i)
        addOp(other.operations[i]);

    addOp("Присвоен оператором =");
    return *this;
}

Object::~Object()
{
    totalActive--;
    clearOp();
}

void Object::addOp(const std::string& op)
{
    if (opCount == opCapacity)
    {
        int newCap = (opCapacity == 0) ? 4 : opCapacity * 2;
        std::string* newOps = new std::string[newCap];
        for (int i = 0; i < opCount; ++i)
            newOps[i] = operations[i];
        delete[] operations;
        operations = newOps;
        opCapacity = newCap;
    }
    operations[opCount++] = op;
}

void Object::addOp(const std::string& op) const
{
    // Для const-методов просто выводим в консоль (нельзя менять объект)
    std::cout << "[LOG] " << op << "\n";
}

void Object::clearOp()
{
    delete[] operations;
    operations = nullptr;
    opCount = 0;
    opCapacity = 0;
}

void Object::printOp() const
{
    std::cout << "История операций с объектом:\n";
    for (int i = 0; i < opCount; ++i)
        std::cout << "  " << (i + 1) << ". " << operations[i] << "\n";
    std::cout << std::endl;
}

void Object::printTotalInfo()
{
    std::cout << "=== Статистика объектов ===\n";
    std::cout << "Всего создано объектов: " << totalCreated << "\n";
    std::cout << "Активных объектов сейчас: " << totalActive << "\n\n";
}

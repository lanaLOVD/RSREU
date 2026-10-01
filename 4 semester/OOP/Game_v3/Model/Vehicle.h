#ifndef VEHICLE_H
#define VEHICLE_H

#include "GameObject.h"
#include "GameConstants.h"

/**
 * Машина
 */
class Vehicle : public GameObject
{
public:
    /**
     * Конструктор
     * double x - относительная координата левой стороны
     * double length - относительная длина
     * double speed - относительная скорость
     */
    Vehicle(double x, double length, double speed) : GameObject(x, length, speed)
    {
    }
};

#endif
#ifndef VEHICLE_H
#define VEHICLE_H

#include "GameObject.h"
#include "GameConstants.h"

class Vehicle : public GameObject
{
private:

public:
    Vehicle(double x, double length, double speed) : GameObject(x, length, speed)
    {
    }


    //void update(double elapsedTime) override;
    //void reset(double startX);
    //bool checkCollision(double playerX, double playerY, double playerSize) const;
};

#endif
#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include "GameObject.h"
#include "GameConstants.h"

class Player : public GameObject
{
private:
    int m_coins;

public:
    Player(double startX, double length, double speed)
        : GameObject(startX, length, speed), m_coins(0) {}

    int getCoins() const { return m_coins; }

    void addCoin() { m_coins++; }

    void setX(double x) { GameObject::setX(x); }

    void reset();
};

#endif
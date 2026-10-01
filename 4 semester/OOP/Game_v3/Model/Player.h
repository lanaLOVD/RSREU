#ifndef PLAYER_H
#define PLAYER_H

#include <cmath>
#include "GameObject.h"
#include "GameConstants.h"

/**
 * Игровой персонаж
 */
class Player : public GameObject
{
private:
    /**
     * Собранные монеты
     */
    int m_coins;

public:
    /**
    * Конструктор
    * double startX - начальная относительная координата левой стороны
    * double length - относительная длина
    * double speed - относительная скорость движения
    */
    Player(double startX, double length, double speed)
        : GameObject(startX, length, speed), m_coins(0) {}

    /**
     * Геттер для поля m_coins
     */
    int getCoins() const { return m_coins; }

    /**
     * Увеличение количества собранных монет на 1
     */
    void addCoin() { m_coins++; }
};

#endif
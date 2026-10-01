#ifndef COIN_H
#define COIN_H

#include "GameBonus.h"
#include "GameConstants.h"


/**
 * Монета
 */
class Coin : public GameBonus
{
public:
    /**
     * Конструктор
     * double x - относительная координата левой стороны монеты
     * double length - относительная длина монеты
     */
    Coin(double x, double length);

    /**
     * Переопределение метода взятия бонусного объекта
     */
    void take() override
    {
    }
};

#endif
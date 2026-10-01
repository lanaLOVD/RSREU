#include "Coin.h"


/**
 * Реализация конструктора
 * double x - относительная координата левой стороны монеты
 * double length - относительная длина монеты
*/
Coin::Coin(double x, double length)
    : GameBonus(x, length, GameBonusType::BONUS_COIN)
{
}
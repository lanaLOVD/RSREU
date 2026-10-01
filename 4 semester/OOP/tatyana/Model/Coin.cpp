#include "Coin.h"

Coin::Coin(double x, double length)
    : GameBonus(x, length, GameBonusType::BONUS_COIN)
{
}

bool Coin::operator=(const Coin& other) const {
    return getX() == other.getX();
}

void Coin::reset() {
    // TODO
}
#pragma once
#include "GameObject.h"

/**
 * @brief Монета, которую может собрать игрок.
 *
 * При касании игроком деактивируется и увеличивает счётчик монет игрока.
 * Наследуется от GameObject.
 */
class Coin : public GameObject {
public:
    /**
     * @brief Конструктор монеты.
     * @param x  Координата X
     * @param y  Координата Y
     */
    Coin(double x, double y)
        : GameObject{ x, y, 20, 20 } {}

    /**
     * @brief Обновление состояния монеты.
     *
     * Монета статична — логика не используется.
     */
    void update() override;
};
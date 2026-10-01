#pragma once
#include "GameObject.h"

/**
 * @brief Монета, которую может собрать игрок.
 *
 * При касании игроком деактивируется и увеличивает его счётчик монет.
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
     * @brief Обновление состояния монеты (не используется, монета статична).
     */
    void update() override;
};

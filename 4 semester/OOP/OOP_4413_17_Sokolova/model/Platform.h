#pragma once
#include "GameObject.h"

/**
 * @brief Статическая платформа, по которой ходят игрок и враги.
 *
 * Не имеет собственной логики обновления — является неподвижным объектом мира.
 * Наследуется от GameObject.
 */
class Platform : public GameObject {
public:
    /**
     * @brief Конструктор платформы.
     * @param x  Координата X левого края
     * @param y  Координата Y верхнего края
     * @param w  Ширина платформы в пикселях
     * @param h  Высота платформы в пикселях
     */
    Platform(double x, double y, double w, double h)
        : GameObject{ x, y, w, h } {}

    /**
     * @brief Обновление состояния платформы.
     *
     * Платформа статична — логика не используется.
     */
    void update() override;
};
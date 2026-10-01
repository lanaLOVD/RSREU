#include "Enemy.h"

/**
 * @brief Обновляет горизонтальное положение врага.
 *
 * Перемещает врага в текущем направлении на величину m_speed.
 */
void Enemy::update() {
    if (m_movingRight) {
        m_x += m_speed;
    } else {
        m_x -= m_speed;
    }
}

/**
 * @brief Применяет гравитацию и обрабатывает приземление на платформы.
 *
 * Если враг не на земле — увеличивает вертикальную скорость.
 * При столкновении с верхней поверхностью платформы — останавливает падение.
 * Если враг упал ниже y=700 — деактивируется.
 *
 * @param platforms  Список всех платформ в мире
 */
void Enemy::applyGravity(const std::vector<std::unique_ptr<Platform>>& platforms) {
    if (!m_isOnGround) {
        m_velocityY += m_gravity;
    }

    m_y += m_velocityY;

    m_isOnGround = false;
    for (const auto& platform : platforms) {
        if (platform && platform->getActive() && collidesWith(*platform)) {
            if (m_velocityY > 0 && m_y < platform->getY()) {
                m_y = platform->getY() - m_height;
                m_velocityY = 0;
                m_isOnGround = true;
                checkPlatformEdge(*platform);
                break;
            }
        }
    }

    // Враг выпал за нижнюю границу мира
    if (m_y > 700) {
        setActive(false);
    }
}

/**
 * @brief Разворачивает врага, если он достиг края платформы.
 *
 * @param platform  Платформа, на которой стоит враг
 */
void Enemy::checkPlatformEdge(const Platform& platform) {
    double platformLeft  = platform.getX();
    double platformRight = platform.getX() + platform.getWidth();
    double enemyCenter   = m_x + m_width / 2;

    if (m_movingRight && enemyCenter >= platformRight - 10) {
        m_movingRight = false;
    } else if (!m_movingRight && enemyCenter <= platformLeft + 10) {
        m_movingRight = true;
    }
}

/**
 * @brief Возвращает горизонтальную скорость врага.
 * @return Скорость (пикселей за тик)
 */
double Enemy::getSpeed() const {
    return m_speed;
}

/**
 * @brief Возвращает направление движения.
 * @return true, если враг движется вправо
 */
bool Enemy::isMovingRight() const {
    return m_movingRight;
}

/**
 * @brief Возвращает флаг нахождения на земле.
 * @return true, если враг стоит на платформе
 */
bool Enemy::isGrounded() const {
    return m_isOnGround;
}

/**
 * @brief Возвращает текущую вертикальную скорость.
 * @return Вертикальная скорость
 */
double Enemy::getVelocityY() const {
    return m_velocityY;
}

#include "Player.h"

/**
 * @brief Устанавливает количество жизней игрока.
 * @param lives  Новое значение жизней
 */
void Player::setLives(int lives) {
    m_lives = lives;
}

/**
 * @brief Возвращает текущую вертикальную скорость.
 * @return Вертикальная скорость (положительная — вниз)
 */
double Player::getVelocityY() const {
    return m_velocityY;
}

/**
 * @brief Возвращает текущую горизонтальную скорость.
 * @return Горизонтальная скорость
 */
double Player::getVelocityX() const {
    return m_velocityX;
}

/**
 * @brief Возвращает флаг неуязвимости.
 * @return true, если игрок сейчас неуязвим
 */
bool Player::getIsInvulnerable() const {
    return m_isInvulnerable;
}

/**
 * @brief Запускает прыжок, если игрок не находится в воздухе.
 */
void Player::jump() {
    if (!m_isJumping) {
        m_velocityY = -12;
        m_isJumping = true;
    }
}

/**
 * @brief Задаёт движение влево.
 */
void Player::moveLeft() {
    m_velocityX = -15;
}

/**
 * @brief Задаёт движение вправо.
 */
void Player::moveRight() {
    m_velocityX = 15;
}

/**
 * @brief Применяет горизонтальное трение (замедляет движение).
 */
void Player::stop() {
    m_velocityX *= 0.8;
}

/**
 * @brief Возвращает количество оставшихся жизней.
 * @return Количество жизней
 */
int Player::getLives() const {
    return m_lives;
}

/**
 * @brief Возвращает количество собранных монет.
 * @return Количество монет
 */
int Player::getCoins() const {
    return m_coins;
}

/**
 * @brief Увеличивает счётчик монет на 1.
 */
void Player::addCoin() {
    m_coins++;
}

/**
 * @brief Наносит урон игроку.
 *
 * Уменьшает жизни, включает временную неуязвимость.
 * Если жизни кончились — деактивирует объект.
 */
void Player::takeDamage() {
    if (m_isInvulnerable) {
        return;
    }

    m_lives--;
    setInvulnerable(true, 2.0f);

    if (m_lives > 0) {
        respawn();
    } else {
        setActive(false);
    }
}

/**
 * @brief Перемещает игрока в стартовую позицию и сбрасывает скорость.
 */
void Player::respawn() {
    m_x = 100;
    m_y = 300;
    m_velocityY = 0;
    m_velocityX = 0;
    m_isJumping = false;
}

/**
 * @brief Останавливает вертикальное движение при приземлении на платформу.
 */
void Player::stopJump() {
    if (m_velocityY < 0) m_velocityY = 0;
    m_isJumping = false;
}

/**
 * @brief Включает или выключает режим неуязвимости.
 * @param invuln    true — включить неуязвимость
 * @param duration  Длительность неуязвимости в секундах
 */
void Player::setInvulnerable(bool invuln, float duration) {
    m_isInvulnerable = invuln;
    m_invulnerabilityTimer = invuln ? duration : 0.0f;
}

/**
 * @brief Обновляет физическое состояние игрока за один тик.
 *
 * Применяет гравитацию, перемещает объект, отсчитывает неуязвимость,
 * обрабатывает выпадение за нижнюю границу мира.
 */
void Player::update() {
    // Таймер неуязвимости
    if (m_isInvulnerable) {
        m_invulnerabilityTimer -= 1.0f / 60.0f;
        if (m_invulnerabilityTimer <= 0.0f) {
            setInvulnerable(false);
        }
    }

    // Гравитация и перемещение
    m_velocityY += m_gravity;
    m_x += m_velocityX;
    m_y += m_velocityY;

    // Ограничение максимальной скорости падения
    if (m_velocityY > 15) m_velocityY = 15;

    // Выпадение за нижнюю границу мира
    if (m_y > 700) {
        takeDamage();
        if (m_lives > 0) {
            setPosition(100, 300);
            m_velocityX = 0;
            m_velocityY = 0;
            m_isJumping = false;
        }
    }
}

/**
 * @brief Полностью сбрасывает состояние игрока в начальное.
 */
void Player::reset() {
    setPosition(100, 300);
    m_velocityX = 0;
    m_velocityY = 0;
    m_isJumping = false;
    m_lives = 1;
    m_coins = 0;
    m_isInvulnerable = false;
    m_invulnerabilityTimer = 0.0f;
    setActive(true);
}

#pragma once
#include "GameObject.h"

/**
 * @brief Класс игрока, управляемого пользователем.
 *
 * Отвечает за движение, прыжок, получение урона, неуязвимость и счёт монет.
 */
class Player : public GameObject {
private:
    /// @brief Горизонтальная скорость (пикселей за тик)
    double m_velocityX;

    /// @brief Вертикальная скорость (пикселей за тик); положительная — вниз
    double m_velocityY;

    /// @brief Ускорение гравитации (добавляется к m_velocityY каждый тик)
    double m_gravity;

    /// @brief Флаг: игрок находится в прыжке
    bool m_isJumping;

    /// @brief Количество оставшихся жизней
    int m_lives;

    /// @brief Количество собранных монет
    int m_coins;

    /// @brief Флаг неуязвимости (после получения урона)
    bool m_isInvulnerable;

    /// @brief Оставшееся время неуязвимости (в секундах)
    float m_invulnerabilityTimer;

public:
    /**
     * @brief Конструктор игрока.
     * @param x  Начальная координата X
     * @param y  Начальная координата Y
     */
    Player(double x, double y)
        : GameObject{ x, y, 30, 50 },
          m_velocityX{ 0 }, m_velocityY{ 0 },
          m_gravity{ 0.5 }, m_isJumping{ true },
          m_lives{ 1 }, m_coins{ 0 },
          m_isInvulnerable{ false }, m_invulnerabilityTimer{ 0.0f } {}

    /** @brief Запускает прыжок, если игрок стоит на земле */
    void jump();

    /** @brief Движение влево */
    void moveLeft();

    /** @brief Движение вправо */
    void moveRight();

    /** @brief Замедляет горизонтальное движение (трение) */
    void stop();

    /** @brief Возвращает количество оставшихся жизней */
    int getLives() const;

    /** @brief Возвращает количество собранных монет */
    int getCoins() const;

    /** @brief Увеличивает счётчик монет на 1 */
    void addCoin();

    /** @brief Уменьшает жизни, включает неуязвимость и при необходимости воскрешает */
    void takeDamage();

    /** @brief Перемещает игрока в стартовую позицию после смерти */
    void respawn();

    /**
     * @brief Устанавливает количество жизней.
     * @param lives  Новое значение жизней
     */
    void setLives(int lives);

    /** @brief Останавливает вертикальное движение при приземлении на платформу */
    void stopJump();

    /** @brief Обновляет физику игрока за один тик */
    void update() override;

    /** @brief Возвращает флаг неуязвимости */
    bool getIsInvulnerable() const;

    /**
     * @brief Включает или выключает неуязвимость.
     * @param invuln    true — включить неуязвимость
     * @param duration  Продолжительность в секундах (по умолчанию 2.0)
     */
    void setInvulnerable(bool invuln, float duration = 2.0f);

    /** @brief Возвращает текущую вертикальную скорость */
    double getVelocityY() const;

    /** @brief Возвращает текущую горизонтальную скорость */
    double getVelocityX() const;

    /** @brief Сбрасывает игрока в начальное состояние */
    void reset();
};

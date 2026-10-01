#pragma once
#include "GameObject.h"
#include "Platform.h"

/**
 * @brief Враг, патрулирующий платформу.
 *
 * Движется горизонтально, разворачивается у края платформы.
 * Падает под действием гравитации. Если игрок прыгает сверху — уничтожается.
 */
class Enemy : public GameObject {
private:
    /// @brief Горизонтальная скорость движения (пикселей за тик)
    double m_speed;

    /// @brief Направление движения: true — вправо, false — влево
    bool m_movingRight;

    /// @brief Ускорение гравитации
    double m_gravity;

    /// @brief Текущая вертикальная скорость
    double m_velocityY;

    /// @brief Флаг: враг стоит на земле/платформе
    bool m_isOnGround;

    /**
     * @brief Проверяет, достиг ли враг края платформы, и разворачивает его.
     * @param platform  Платформа, на которой стоит враг
     */
    void checkPlatformEdge(const Platform& platform);

public:
    /**
     * @brief Конструктор врага.
     * @param x            Начальная координата X
     * @param y            Начальная координата Y
     * @param speed        Скорость горизонтального движения
     * @param movingRight  Начальное направление (true — вправо)
     */
    Enemy(double x, double y, double speed, bool movingRight)
        : GameObject{ x, y, 40, 40 },
          m_speed{ speed }, m_movingRight{ movingRight },
          m_gravity{ 0.5 }, m_velocityY{ 0 }, m_isOnGround{ false } {}

    /**
     * @brief Конструктор копирования.
     * @param other  Копируемый враг
     */
    Enemy(const Enemy& other)
        : GameObject{ other },
          m_speed{ other.m_speed }, m_movingRight{ other.m_movingRight },
          m_gravity{ other.m_gravity }, m_velocityY{ other.m_velocityY },
          m_isOnGround{ other.m_isOnGround } {}

    /**
     * @brief Обновляет горизонтальное положение врага за один тик.
     */
    void update() override;

    /**
     * @brief Применяет гравитацию и обрабатывает столкновения с платформами.
     * @param platforms  Список всех платформ в мире
     */
    void applyGravity(const std::vector<std::unique_ptr<Platform>>& platforms);

    /** @brief Возвращает горизонтальную скорость врага */
    double getSpeed() const;

    /** @brief Возвращает true, если враг движется вправо */
    bool isMovingRight() const;

    /** @brief Возвращает true, если враг стоит на земле */
    bool isGrounded() const;

    /** @brief Возвращает текущую вертикальную скорость */
    double getVelocityY() const;
};

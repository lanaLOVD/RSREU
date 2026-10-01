#pragma once
#include <vector>
#include <memory>

/**
 * @brief Базовый класс для всех игровых объектов.
 *
 * Хранит позицию, размеры и флаг активности объекта.
 * Все игровые объекты (игрок, враги, монеты, платформы) наследуются от этого класса.
 */
class GameObject {
protected:
    /// @brief Координата X левого верхнего угла объекта
    double m_x;

    /// @brief Координата Y левого верхнего угла объекта
    double m_y;

    /// @brief Ширина объекта
    double m_width;

    /// @brief Высота объекта
    double m_height;

    /// @brief Флаг активности: false — объект считается удалённым
    bool m_isActive;

public:
    /**
     * @brief Конструктор игрового объекта.
     * @param x      Начальная координата X
     * @param y      Начальная координата Y
     * @param w      Ширина объекта
     * @param h      Высота объекта
     */
    GameObject(double x, double y, double w, double h)
        : m_x{ x }, m_y{ y }, m_width{ w }, m_height{ h }, m_isActive{ true } {}

    /**
     * @brief Конструктор копирования.
     * @param other  Копируемый объект
     */
    GameObject(const GameObject& other)
        : m_x{ other.m_x }, m_y{ other.m_y },
          m_width{ other.m_width }, m_height{ other.m_height },
          m_isActive{ other.m_isActive } {}

    /// @brief Виртуальный деструктор
    virtual ~GameObject() = default;

    /** @brief Возвращает координату X */
    double getX() const;

    /** @brief Возвращает координату Y */
    double getY() const;

    /** @brief Возвращает ширину объекта */
    double getWidth() const;

    /** @brief Возвращает высоту объекта */
    double getHeight() const;

    /** @brief Возвращает флаг активности объекта */
    bool getActive() const;

    /**
     * @brief Устанавливает новую позицию объекта.
     * @param nx  Новая координата X
     * @param ny  Новая координата Y
     */
    void setPosition(double nx, double ny);

    /**
     * @brief Устанавливает новые размеры объекта.
     * @param w  Новая ширина
     * @param h  Новая высота
     */
    void setSize(double w, double h);

    /**
     * @brief Устанавливает флаг активности.
     * @param active  true — объект активен, false — деактивирован
     */
    void setActive(bool active);

    /**
     * @brief Обновляет состояние объекта за один игровой тик.
     *        Чисто виртуальная функция, реализуется в каждом подклассе.
     */
    virtual void update() = 0;

    /**
     * @brief Проверяет столкновение с другим объектом (AABB).
     * @param other  Другой игровой объект
     * @return true, если прямоугольники пересекаются
     */
    bool collidesWith(const GameObject& other) const;
};

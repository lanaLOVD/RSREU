#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

/**
 * Базовый класс для всех игровых сущностей
 */
class GameObject
{
private:
    // Относительная координата x левой стороны объекта
    double m_x;
    // Относительная длина объекта
    double m_length;
    // Относительная скорость движения объекта
    double m_speed;

public:
    /**
    * Конструктор
    * double x - относительная координата x левой стороны объекта
    * double length - относительная длина объекта
    * double speed - относительная скорость движения объекта
    */
    GameObject(double x, double length, double speed)
        : m_x(x), m_length(length), m_speed(speed)
    {
    }

    /**
     * Виртуальный деструктор
     */
    virtual ~GameObject() = default;

    /**
     * Геттер для поля m_x
    */
    double getX() const
    {
        return m_x;
    }

    /**
     * Геттер для поля m_length
     */
    double getLength() const
    {
        return m_length;
    }

    /**
     * Геттер для поля m_speed
     */
    double getSpeed() const
    {
        return m_speed;
    }

    /**
     * Проверка на столкновение с другим объектом
     * const GameObject& other - ссылка на другой игровой объект
     * Возвращает true, если обнаружено столкновение, инача - false
     */
    bool checkCollision(const GameObject& other) const
    {
        return (m_x < other.m_x + other.m_length) &&
               (m_x + m_length > other.m_x);
    }

    /**
     * Передвижение объекта по оси X
     * double dx - изменение относительной координаты левой стороны объекта
     */
    virtual void move(double dx)
    {
        m_x += dx;
    }

    /**
     * Проверка объектов на равенство
     * const GameObject& other - ссылка на другой игровой объект
     */
    virtual bool operator==(const GameObject& other) const {
        return m_x == other.m_x && m_length == other.m_length;
    }
};

#endif
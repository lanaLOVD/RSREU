#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject {
protected:
    double m_x;
    double m_length;
    double m_speed;

public:
    GameObject(double x, double length, double speed)
        : m_x(x), m_length(length), m_speed(speed) {}

    virtual ~GameObject() = default;

    double getX() const { return m_x; }
    double getLength() const { return m_length; }
    double getSpeed() const { return m_speed; }

    void setX(double x) { m_x = x; }

    // Основной метод для проверки столкновения
    bool checkCollision(const GameObject& other) const {
        return (m_x < other.m_x + other.m_length) &&
               (m_x + m_length > other.m_x);
    }

    // Добавляем move для Vehicle
    virtual void move(double dx) {
        m_x += dx;
    }
    bool operator==(const GameObject& other) const {
        return m_x == other.m_x && m_length == other.m_length;
    }
};

#endif
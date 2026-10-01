#include "GameObject.h"

/// @brief Возвращает координату X объекта
double GameObject::getX() const {
    return m_x;
}

/// @brief Возвращает координату Y объекта
double GameObject::getY() const {
    return m_y;
}

/// @brief Возвращает ширину объекта
double GameObject::getWidth() const {
    return m_width;
}

/// @brief Возвращает высоту объекта
double GameObject::getHeight() const {
    return m_height;
}

/// @brief Возвращает флаг активности объекта
bool GameObject::getActive() const {
    return m_isActive;
}

/**
 * @brief Устанавливает новую позицию объекта.
 * @param nx  Новая координата X
 * @param ny  Новая координата Y
 */
void GameObject::setPosition(double nx, double ny) {
    m_x = nx;
    m_y = ny;
}

/**
 * @brief Устанавливает новые размеры объекта.
 * @param w  Новая ширина
 * @param h  Новая высота
 */
void GameObject::setSize(double w, double h) {
    m_width = w;
    m_height = h;
}

/**
 * @brief Устанавливает флаг активности.
 * @param active  true — объект активен
 */
void GameObject::setActive(bool active) {
    m_isActive = active;
}

/**
 * @brief Проверяет AABB-столкновение с другим объектом.
 * @param other  Другой игровой объект
 * @return true, если прямоугольники пересекаются
 */
bool GameObject::collidesWith(const GameObject& other) const {
    return m_x < other.m_x + other.m_width &&
           m_x + m_width > other.m_x &&
           m_y < other.m_y + other.m_height &&
           m_y + m_height > other.m_y;
}

#include "GameObject.h"

/**
 * @brief Возвращает координату X левого верхнего угла объекта.
 * @return Координата X
 */
double GameObject::getX() const {
    return m_x;
}

/**
 * @brief Возвращает координату Y левого верхнего угла объекта.
 * @return Координата Y
 */
double GameObject::getY() const {
    return m_y;
}

/**
 * @brief Возвращает ширину объекта.
 * @return Ширина в пикселях
 */
double GameObject::getWidth() const {
    return m_width;
}

/**
 * @brief Возвращает высоту объекта.
 * @return Высота в пикселях
 */
double GameObject::getHeight() const {
    return m_height;
}

/**
 * @brief Возвращает флаг активности объекта.
 * @return true — объект активен
 */
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
 * @brief Устанавливает флаг активности объекта.
 * @param active  true — объект активен, false — деактивирован
 */
void GameObject::setActive(bool active) {
    m_isActive = active;
}

/**
 * @brief Проверяет AABB-столкновение с другим объектом.
 *
 * Использует метод разделяющих осей: если прямоугольники не
 * пересекаются ни по одной оси — столкновения нет.
 *
 * @param other  Другой игровой объект
 * @return true, если прямоугольники пересекаются
 */
bool GameObject::collidesWith(const GameObject& other) const {
    return m_x < other.m_x + other.m_width &&
           m_x + m_width > other.m_x &&
           m_y < other.m_y + other.m_height &&
           m_y + m_height > other.m_y;
}
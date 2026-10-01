//
// Created by TheUser on 08.04.2025.
//

#ifndef SKY_SKYOBJECT_H
#define SKY_SKYOBJECT_H

#include "SkyObjectTypes.h"

class SkyObject {
private:
    double m_x;
    double m_y;
    const int m_type;
public:
    /**
     * Конструктор по умолчанию
     */
    SkyObject(int type) : m_x{0}, m_y{0}, m_type(type) {}
    /**
     * Конструктор
     * @param x Координата X
     * @param y Координата Y
     */
    SkyObject(int type, double x, double y) : m_type{type}, m_x{x}, m_y{y} {}
    /**
     * Базовый метод для инициализации
     */
    virtual void init();
    /**
     * Получение типа объекта
     * @return Тип объекта
     */
    const int getType() const {return m_type;}
    /**
     * Получение координаты X
     * @return Координата X
     */
    double getX() const {return m_x;}
    /**
     * Установка координаты X
     * @param x Новая координата X
     */
    void setX(double x) {m_x = x;}
    /**
     * Получение координаты Y
     * @return Координата Y
     */
    double getY() const {return m_y;}
    /**
     * Установка координаты Y
     * @param x Новая координата Y
     */
    void setY(double y) {m_y = y;}
    /**
     * Вычисление следующего шага
     * @param elapsedTime Время, прошедшее с предыдущего шага
     */
    virtual void calculateNextStep(double elapsedTime) { };
    /**
     * Проверить нужен ли объект или его нужно переинициализировать
     * @return Признак необходимости оставить текущий объект
     */
    virtual bool isSkyObjectNeeded() {return true;}
};


#endif //SKY_SKYOBJECT_H

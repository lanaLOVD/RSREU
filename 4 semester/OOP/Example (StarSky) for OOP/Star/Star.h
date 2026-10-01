//
// Created by User on 08.04.2025.
//

#ifndef STARSKY_STAR_H
#define STARSKY_STAR_H

#include "../Sky/SkyObject.h"

/**
Простая мерцающая звезда
 */
class Star : public SkyObject
{
private:
    double m_r;
    double m_rs;
protected:
    /**
     * Конструктор по умолчанию
     */
    Star(int type) : m_r{0}, m_rs{0}, SkyObject{type} { };
    /**
     * Конструктор
     * @param x Координата X
     * @param y Координата Y
     * @param r Радиус
     */
    Star(int type, double x, double y, double r) : m_r{r}, m_rs{0}, SkyObject(type, x, y) { }
public:
    /**
     * Конструктор по умолчанию
     */
    Star() : m_r{0}, m_rs{0}, SkyObject{SkyObjectTypes::STAR} { };
    /**
     * Конструктор
     * @param x Координата X
     * @param y Координата Y
     * @param r Радиус
     */
    Star(double x, double y, double r) : m_r{r}, SkyObject{SkyObjectTypes::STAR, x, y} { }
    /**
     * Получение радиуса звезды
     * @return Радиус звезды
     */
    double getR() const {return m_r;}
    /**
     * Получение диаметра звезды
     * @return Диаметр звезды
     */
    double getD() const {return m_r * m_r;}
    /**
     * Установка радиуса звезды
     * @param x Новый радиус звезды
     */
    void setR(double r) {m_r = r;}
    /**
     * Переопределённая функция инициализации
     */
    void init() override;
    /**
     * Вычисление следующего шага
     * @param elapsedTime Прошедшее с момента последнего шага время
     */
    void calculateNextStep(double elapsedTime) override;
    /**
     * Проверить нужен ли объект или его нужно переинициализировать
     * @return Признак необходимости оставить текущий объект
     */
    bool isSkyObjectNeeded() override;
};

#endif //STARSKY_STAR_H

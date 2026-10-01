//
// Created by TheUser on 08.04.2025.
//

#ifndef SKY_MOVEDSTAR_H
#define SKY_MOVEDSTAR_H

#include "../Sky/SkyObject.h"
#include "Star.h"

class MovedStar : public Star {
private:
    double m_dx;
    double m_dy;
    double m_dr;
    double m_s;
    double m_ds;
protected:
    /**
     * Конструктор по умолчанию
     */
    MovedStar(int type) : m_dx{0}, m_dy{0}, m_dr{0}, m_s{0}, m_ds{0}, Star{type} {};

    /**
     * Конструктор
     * @param x Координата X
     * @param y Координата Y
     * @param r Радиус
     */
    MovedStar(int type, double x, double y, double r) : m_dx{0}, m_dy{0}, m_dr{0}, m_s{0}, m_ds{0}, Star{type} {}
public:
    /**
     * Конструктор по умолчанию
     */
    MovedStar() : m_dx{0}, m_dy{0}, m_dr{0}, m_s{0}, m_ds{0}, Star{SkyObjectTypes::MOVED_STAR} {};

    /**
     * Конструктор
     * @param x Координата X
     * @param y Координата Y
     * @param r Радиус
     */
    MovedStar(double x, double y, double r) : m_dx{0}, m_dy{0}, m_dr{0}, m_s{0}, m_ds{0}, Star{SkyObjectTypes::MOVED_STAR} {}
    /**
     * Переопределённая функция инициализации
     */
    void init() override;
    /**
     * Определение начального угла полёта
     * @return Угол полёта
     */
    virtual double calcAngle();
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

#endif //SKY_MOVEDSTAR_H

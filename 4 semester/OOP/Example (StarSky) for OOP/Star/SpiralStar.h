//
// Created by TheUser on 14.04.2025.
//

#ifndef SKY_SPIRALSTAR_H
#define SKY_SPIRALSTAR_H

#include "../Sky/SkyObject.h"
#include "MovedStar.h"

class SpiralStar : public MovedStar
{
private:
    double m_savX;
    double m_savY;
    double m_angle;
public:
    SpiralStar() : m_savX{0}, m_savY{0}, m_angle{0}, MovedStar{SkyObjectTypes::SPIRAL_STAR} {}
    SpiralStar(double angle) : m_savX{0}, m_savY{0}, m_angle{angle}, MovedStar{SkyObjectTypes::SPIRAL_STAR} {}
    double getAngle() {return m_angle;}
    void setAngle(const double angle) {m_angle = angle;}
    /**
     * Переопределённая функция инициализации
     */
    void init() override;
    /**
     * Определение начального угла полёта
     * @return Угол полёта
     */
    double calcAngle() override;
    /**
     * Вычисление следующего шага
     * @param elapsedTime Прошедшее с момента последнего шага время
     */
    void calculateNextStep(double elapsedTime) override;
};


#endif //SKY_SPIRALSTAR_H

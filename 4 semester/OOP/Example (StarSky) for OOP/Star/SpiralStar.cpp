//
// Created by TheUser on 14.04.2025.
//

#include "SpiralStar.h"
#include "../Utils/RND.h"
#include "../Sky/SkySettings.h"

/**
 * Переопределённая функция инициализации
 */
void SpiralStar::init()
{
    MovedStar::init();
    m_savX = getX();
    m_savY = getY();
}
/**
 * Определение начального угла полёта
 * @return Угол полёта
 */
double SpiralStar::calcAngle()
{
    m_angle = RND::instance().get(0.0, std::numbers::pi * 2);
    return m_angle;
}
/**
 * Вычисление следующего шага
 * @param elapsedTime Прошедшее время в секундах
 */
void SpiralStar::calculateNextStep(double elapsedTime)
{
    static SkySettings& settings = SkySettings::instance();
    setX(m_savX);
    setY(m_savY);
    MovedStar::calculateNextStep(elapsedTime);
    m_savX = getX();
    m_savY = getY();
    m_angle += settings.getSpiralSpeed() * elapsedTime;
    if (m_angle > std::numbers::pi * 2.0)
        m_angle -= std::numbers::pi * 2.0;
    double x = getX() - settings.getWidth() / 2.0;
    double y = getY() - settings.getHeight() / 2.0;
    double len = std::sqrt(x*x + y*y);
    setX(settings.getWidth() / 2.0 + len * std::cos(m_angle));
    setY(settings.getHeight() / 2.0 + len * std::sin(m_angle));
}

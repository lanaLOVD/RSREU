//
// Created by TheUser on 08.04.2025.
//

#include "MovedStar.h"
#include "../Utils/RND.h"
#include "../Sky/SkySettings.h"

/**
 * Переопределённая функция инициализации
 */
void MovedStar::init()
{
    const SkySettings& settings = SkySettings::instance();
    double width{settings.getWidth()};
    double height{settings.getHeight()};
    double x1{width / 2};
    double y1{height / 2};
    double x2{0};
    double y2{0};

    double angle = calcAngle();
    double sourceLen = std::sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1));
    double targetLen = RND::instance().get(sourceLen * settings.getMinTargetLenMultiplier(), sourceLen * settings.getMaxTargetLenMultiplier());

    x2 = x1 + targetLen * std::cos(angle);
    y2 = y1 + targetLen * std::sin(angle);

    double startLen = RND::instance().get(0.0, settings.getMaxStartRadius());
    x1 = x1 + startLen * std::cos(angle);
    y1 = y1 + startLen * std::sin(angle);

    setX(x1);
    setY(y1);
    m_dx = (x2 - x1) / (x1);
    m_dy = (y2 - y1) / (y1);
    setR(settings.getMinRadius());

    m_dr = (settings.getMaxRadius() * settings.getMaxRadiusMultiplier() - settings.getMinRadius()) / sourceLen;
    m_ds = (settings.getMaxSpeed() - settings.getMinSpeed()) / sourceLen;
    m_s = settings.getMinSpeed();
}
/**
 * Определение начального угла полёта
 * @return Угол полёта
 */
double MovedStar::calcAngle()
{
   return RND::instance().get(0.0, std::numbers::pi * 2);
}
/**
 * Вычисление следующего шага
 * @param elapsedTime Прошедшее время в секундах
 */
void MovedStar::calculateNextStep(double elapsedTime)
{
    static SkySettings& settings = SkySettings::instance();

    setX(getX() + (m_dx * m_s) * elapsedTime);
    setY(getY() + (m_dy * m_s) * elapsedTime);
    setR(getR() + m_dr * m_s * elapsedTime);
    m_ds += m_ds * elapsedTime;
    m_s += m_ds;
}

/**
* Проверить нужен ли объект или его нужно переинициализировать
* @return Признак необходимости оставить текущий объект
*/
bool MovedStar::isSkyObjectNeeded()
{
    static SkySettings& settings = SkySettings::instance();
    return !(getX() < 0 || getX() > settings.getWidth() || getY() < 0 || getY() > settings.getHeight());
}

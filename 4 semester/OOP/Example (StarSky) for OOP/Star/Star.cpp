//
// Created by User on 08.04.2025.
//

#include "Star.h"
#include "../Utils/RND.h"
#include "../Sky/SkySettings.h"

/**
 * Переопределённая функция инициализации
 */
void Star::init()
{
    const SkySettings& settings = SkySettings::instance();
    SkyObject::init();
    m_r = RND::instance().get(settings.getMinRadius(), settings.getMaxRadius());
    m_rs = settings.getRadiusChangeSpeed();
}

/**
 * Вычисление следующего шага
 * @param elapsedTime Прошедшее время в секундах
 */
void Star::calculateNextStep(double elapsedTime)
{
    static SkySettings& settings = SkySettings::instance();
    m_r += m_rs * elapsedTime;
    if (m_r > settings.getMaxRadius())
        m_rs *= -1.0;
}

/**
     * Проверить нужен ли объект или его нужно переинициализировать
     * @return Признак необходимости оставить текущий объект
     */
bool Star::isSkyObjectNeeded()
{
    static SkySettings& settings = SkySettings::instance();
    return m_r >= settings.getMinRadius();
}

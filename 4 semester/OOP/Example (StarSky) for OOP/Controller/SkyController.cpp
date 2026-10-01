//
// Created by TheUser on 15.04.2025.
//

#include "SkyController.h"
#include "../Sky/SkySettings.h"

SkyController::SkyController(std::shared_ptr<Sky> sky, StarSkyDrawing& starSkyDrawing) : m_sky {sky}, m_starSkyDrawing{starSkyDrawing}
{
    m_starSkyDrawing.setSky(m_sky);
    auto funcIncreaseStarsCount = std::bind(&SkyController::increaseStarsCount, this);
    m_starSkyDrawing.setKeyPlusCallback(funcIncreaseStarsCount);
    auto funcDecreaseStarsCount = std::bind(&SkyController::decreaseStarsCount, this);
    m_starSkyDrawing.setKeyMinusCallback(funcDecreaseStarsCount);
}

void SkyController::increaseStarsCount()
{
    SkySettings& settings = SkySettings::instance();
    int maxStars = settings.getMaxStars();
    if (maxStars + c_starsDelta < c_maxTotalStars)
        settings.setMaxStars(maxStars + c_starsDelta);
    else
        settings.setMaxStars(c_maxTotalStars);
}

void SkyController::decreaseStarsCount()
{
    SkySettings& settings = SkySettings::instance();
    int maxStars = settings.getMaxStars();
    if (maxStars - c_starsDelta > c_minTotalStars)
        settings.setMaxStars(maxStars - c_starsDelta);
    else
        settings.setMaxStars(c_minTotalStars);
}
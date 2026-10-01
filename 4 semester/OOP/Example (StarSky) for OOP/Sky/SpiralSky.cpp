//
// Created by TheUser on 14.04.2025.
//

#include "SpiralSky.h"
#include "../Star/SpiralStar.h"

std::unique_ptr<SkyObject> SpiralSky::createSkyObject()
{
    std::unique_ptr<SkyObject> so{new SpiralStar{}};
    so->init();
    return so;
}
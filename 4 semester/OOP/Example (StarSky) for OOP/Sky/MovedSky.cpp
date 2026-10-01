//
// Created by TheUser on 08.04.2025.
//

#include "MovedSky.h"
#include "../Star/MovedStar.h"

std::unique_ptr<SkyObject> MovedSky::createSkyObject()
{
    std::unique_ptr<SkyObject> so{new MovedStar{}};
    so->init();
    return so;
}
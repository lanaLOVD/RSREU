//
// Created by TheUser on 14.04.2025.
//

#ifndef SKY_SPIRALSKY_H
#define SKY_SPIRALSKY_H

#include "MovedSky.h"

class SpiralSky : public MovedSky
{
protected:
    std::unique_ptr<SkyObject> createSkyObject() override;
public:
    SpiralSky() : MovedSky{} {}
};


#endif //SKY_SPIRALSKY_H

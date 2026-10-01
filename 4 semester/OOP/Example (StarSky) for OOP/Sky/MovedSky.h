//
// Created by TheUser on 08.04.2025.
//

#ifndef SKY_MOVEDSKY_H
#define SKY_MOVEDSKY_H

#include "Sky.h"

class MovedSky : public Sky
{
protected:
    std::unique_ptr<SkyObject> createSkyObject() override;
public:
    MovedSky() : Sky{} {}
};


#endif //SKY_MOVEDSKY_H

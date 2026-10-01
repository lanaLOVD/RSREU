//
// Created by TheUser on 08.04.2025.
//

#include "SkyObject.h"
#include "SkySettings.h"
#include "../Utils/RND.h"

void SkyObject::init()
{
    SkySettings& settings = SkySettings::instance();
    m_x = RND::instance().get(0.0, settings.getWidth());
    m_y = RND::instance().get(0.0, settings.getHeight());
}
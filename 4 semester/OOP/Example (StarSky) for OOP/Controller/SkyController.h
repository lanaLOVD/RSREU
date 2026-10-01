//
// Created by User on 08.04.2025.
//

#ifndef SKY_SKYCONTROLLER_H
#define SKY_SKYCONTROLLER_H

#include "../Sky/Sky.h"
#include "../View/StarSkyDrawing.h"

class SkyController {
private:
    const int c_starsDelta = 10;
    const int c_maxTotalStars = 500;
    const int c_minTotalStars = 1;
private:
    std::shared_ptr<Sky> m_sky;
    StarSkyDrawing& m_starSkyDrawing;
public:
    SkyController(std::shared_ptr<Sky> sky, StarSkyDrawing& starSkyDrawing);
    void increaseStarsCount();
    void decreaseStarsCount();
    ~SkyController()
    {
        //delete m_sky;
        //m_starSkyDrawing.setSky(nullptr);
    }
};


#endif //SKY_SKYCONTROLLER_H

//
// Created by User on 08.04.2025.
//

#ifndef SKY_STARSKYDRAWING_H
#define SKY_STARSKYDRAWING_H

#include <FL/Fl.H>
#include <FL/Fl_Widget.H>
#include <map>
#include <functional>
#include "../Star/Star.h"
#include "../Sky/Sky.h"
#include "../Sky/SkyObjectTypes.h"
#include "SkyObjectDrawing.h"

class StarSkyDrawing : public Fl_Widget
{
private:
    enum keys
    {
        MINUS_KEY = 45,
        PLUS_KEY = 61,
        NUM_MINUS_KEY = 65453,
        NUM_PLUS_KEY = 65451
    };
private:
    double m_timeout;
    std::shared_ptr<Sky> m_sky;
    std::map<int, std::unique_ptr<SkyObjectDrawing>> m_map;
    bool m_hasTimeout;
    std::function<void(void)> m_keyMinusCallback;
    std::function<void(void)> m_keyPlusCallback;
    void draw() FL_OVERRIDE;
    static void timeoutEvent(void *);
protected:
    int handle(int) FL_OVERRIDE;
public:
    StarSkyDrawing(int x, int y, int w, int h);
    ~StarSkyDrawing();
    void setSky(std::shared_ptr<Sky> sky);
    void setKeyMinusCallback(std::function<void(void)> callback) {m_keyMinusCallback = callback;};
    void setKeyPlusCallback(std::function<void(void)> callback) {m_keyPlusCallback = callback;};
};


#endif //SKY_STARSKYDRAWING_H

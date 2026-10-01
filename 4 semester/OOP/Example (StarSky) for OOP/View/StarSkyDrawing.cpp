//
// Created by User on 08.04.2025.
//

#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include "../Sky/SkyObjectTypes.h"
#include "StarSkyDrawing.h"
#include "StarDrawing.h"

StarSkyDrawing::StarSkyDrawing(int x, int y, int w, int h) : m_timeout{1.0 / 30.0}, m_sky{nullptr}, m_map{}, m_hasTimeout{
        false}, m_keyMinusCallback {nullptr}, m_keyPlusCallback {nullptr}, Fl_Widget(x, y, w, h)
{
    auto key = SkyObjectTypes::STAR;
    m_map[key] = std::make_unique<StarDrawing>();
    key = SkyObjectTypes::MOVED_STAR;
    m_map[key] = std::make_unique<StarDrawing>();
    key = SkyObjectTypes::SPIRAL_STAR;
    m_map[key] = std::make_unique<StarDrawing>();
}

void StarSkyDrawing::draw()
{
    fl_push_clip(x(), y(), w(), h());
    fl_color(FL_BLACK);
    fl_rectf(x(), y(), w(), h());
    if (m_sky != nullptr)
    {
        m_sky->lock();
        for (auto& skyObject: m_sky->getListOfSkyObjects())
        {
            if (m_map.contains(skyObject->getType()))
            {
                SkyObjectDrawing& drawing = *m_map[skyObject->getType()].get();
                const auto& skyObj = *skyObject.get();
                drawing.draw(*this, skyObj);
            }
        }
        m_sky->unlock();
    }
    fl_pop_clip();
}

int StarSkyDrawing::handle(int event)
{
    int res = Fl_Widget::handle(event);
    switch (event)
    {
        case FL_KEYUP:
            int ekey = Fl::event_key();
            switch (ekey)
            {
                case MINUS_KEY:
                case NUM_MINUS_KEY:
                    if (m_keyMinusCallback != nullptr)
                        m_keyMinusCallback();
                    break;
                case PLUS_KEY:
                case NUM_PLUS_KEY:
                    if (m_keyPlusCallback != nullptr)
                        m_keyPlusCallback();
                    break;
            }
            break;
    }
    return res;
}

void StarSkyDrawing::setSky(std::shared_ptr<Sky> sky)
{
    m_sky = sky;
    if (!m_hasTimeout)
    {
        m_hasTimeout = true;
        Fl::add_timeout(m_timeout, timeoutEvent, this);
    }
}

void StarSkyDrawing::timeoutEvent(void *p)
{
    StarSkyDrawing& starSkyDrawing = * static_cast<StarSkyDrawing*>(p);
    starSkyDrawing.parent()->redraw();
    Fl::repeat_timeout(starSkyDrawing.m_timeout, timeoutEvent, &starSkyDrawing);
}

StarSkyDrawing::~StarSkyDrawing()
{
    m_map.clear();
}



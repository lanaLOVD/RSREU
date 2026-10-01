//
// Created by User on 08.04.2025.
//

#include <FL/Fl.H>
#include <chrono>
#include "Sky.h"
#include "immintrin.h"
#include "../Utils/RND.h"
#include "SkySettings.h"

using namespace std::chrono;

std::unique_ptr<SkyObject> Sky::createSkyObject()
{
    std::unique_ptr<SkyObject> so{new Star{}};
    so->init();
    return so;
}

void Sky::calculateNextStep()
{
    static SkySettings& settings = SkySettings::instance();

    bool isFirst = m_skyObjects.size() == 0;
    m_mutex.lock();
    if (m_skyObjects.size() < settings.getMaxStars())
        m_skyObjects.push_back(createSkyObject());

    if (isFirst)
    {
        m_lastTime = steady_clock::now();
        m_mutex.unlock();
        return;
    }
    time_point<steady_clock> curentTime = steady_clock::now();
    auto elapsed = duration_cast<nanoseconds >(curentTime - m_lastTime);
    double seconds = (double)elapsed.count() / 1000000000.0;
    m_lastTime = curentTime;

    std::list<std::unique_ptr<SkyObject>>::iterator i = m_skyObjects.begin();
    while (i != m_skyObjects.end())
    //for(auto& star : m_skyObjects)
    {
        i->get()->calculateNextStep(seconds);
        if (!(i->get()->isSkyObjectNeeded()))
        {
            if (m_skyObjects.size() > settings.getMaxStars())
                i = m_skyObjects.erase(i);
            else
            {
                i->get()->init();
                ++i;
            }
        }
        else
            ++i;
    }
    m_mutex.unlock();
    std::this_thread::sleep_for(std::chrono::milliseconds(50));
}

void Sky::work(Sky &sky)
{
    while(!sky.m_needStop)
        sky.calculateNextStep();
}

Sky::~Sky()
{
    m_needStop = true;
    m_thread.join();

    m_mutex.lock();
    m_skyObjects.clear();
    m_mutex.unlock();
}

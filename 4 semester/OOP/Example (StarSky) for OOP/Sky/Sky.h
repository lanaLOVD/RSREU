//
// Created by User on 08.04.2025.
//

#ifndef STARSKY_SKY_H
#define STARSKY_SKY_H

#include <list>
#include <chrono>
#include <thread>
#include "../Star/Star.h"

class Sky
{
private:
    std::chrono::time_point<std::chrono::steady_clock> m_lastTime;
    std::list<std::unique_ptr<SkyObject>> m_skyObjects;
    bool m_needStop;
    std::mutex m_mutex;
    std::thread m_thread;
    static void work(Sky&);
protected:
    virtual std::unique_ptr<SkyObject> createSkyObject();
public:
    Sky() :
            m_lastTime {},
            m_skyObjects {},
            m_needStop {false},
            m_mutex {},
            m_thread {work, std::ref(*this)}
        {}
    ~Sky();
    const std::list<std::unique_ptr<SkyObject>>& getListOfSkyObjects() const {return m_skyObjects;}
    void calculateNextStep();
    void lock() {m_mutex.lock();}
    void unlock() {m_mutex.unlock();}
};


#endif //STARSKY_SKY_H

#ifndef COIN_H
#define COIN_H

#include "GameBonus.h"
#include "GameConstants.h"

class Coin : public GameBonus
{
private:
    //bool m_isCollected;
    //double m_size;

public:
    Coin(double x, double length);

    bool operator=(const Coin& other) const;

    /*bool isCollected() const
    {
        return m_isCollected;
    }*/

  /*  double getSize() const
    {
        return m_size;
    }*/

    /*void collect()
    {
        m_isCollected = true;
    }*/

    //void update(double elapsedTime) override;
    void reset();
    //bool checkCollision(double playerX, double playerSize) const;
};

#endif
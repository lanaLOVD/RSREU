#include "Vehicle.h"
//#include "../Utils/RND.h

//void Vehicle::update(double elapsedTime)
//{
//    double moveDistance = m_speed * elapsedTime;
//
//    if (m_movingRight)
//    {
//        /*
//        m_x += moveDistance;
//
//        if (m_x > GameConstants::c_fieldWidth)
//        {
//            m_x = -m_width;
//        }
//        */
//    }
//    else
//    {
//        /*
//        m_x -= moveDistance;
//        if (m_x + m_width < 0)
//        {
//            m_x = GameConstants::c_fieldWidth;
//        }
//        */
//    }
//}

//void Vehicle::reset(double startX)
//{
//    //m_x = startX;
//}

//bool Vehicle::checkCollision(double playerX, double playerY, double playerSize) const
//{
//    return (playerX < getX() + m_width &&
//        playerX + playerSize > getX() &&
//        playerY < getY() + m_height &&
//        playerY + playerSize > getY());
//}
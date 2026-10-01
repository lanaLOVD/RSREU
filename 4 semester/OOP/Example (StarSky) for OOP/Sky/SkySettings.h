//
// Created by TheUser on 08.04.2025.
//

#ifndef SKY_SKYSETTINGS_H
#define SKY_SKYSETTINGS_H

#include "../Controller/SkyController.h"

/**
 * Настройки
 */
class SkySettings
{
private:
    const int c_maxStars = 1;
    const double c_width = 1000;
    const double c_height = 1000;
    const double c_minRadius = 1;
    const double c_maxRadius = 2;
    const double c_radiusChangeSpeed = 0.8;
    const double c_minSpeed = 1;
    const double c_maxSpeed = 5;
    const double c_minTargetLenMultiplier = 3;
    const double c_maxTargetLenMultiplier = 4;
    const double c_maxStartRadius = 20;
    const double c_maxRadiusMultiplier = 5;
    const double c_spiralSpeed = std::numbers::pi * 20.0 / 180.0;
private:
    int m_maxStars;
    double m_width;
    double m_height;
    double m_minRadius;
    double m_maxRadius;
    double m_radiusChangeSpeed;
    double m_minSpeed;
    double m_maxSpeed;
    double m_minTargetLenMultiplier;
    double m_maxTargetLenMultiplier;
    double m_maxStartRadius;
    double m_maxRadiusMultiplier;
    double m_spiralSpeed;
    std::shared_ptr<SkyController> m_controller;
    SkySettings() :
        m_maxStars{c_maxStars},
        m_width{c_width},
        m_height{c_height},
        m_minRadius{c_minRadius},
        m_maxRadius{c_maxRadius},
        m_radiusChangeSpeed{c_radiusChangeSpeed},
        m_minSpeed{c_minSpeed},
        m_maxSpeed{c_maxSpeed},
        m_minTargetLenMultiplier{c_minTargetLenMultiplier},
        m_maxTargetLenMultiplier{c_maxTargetLenMultiplier},
        m_maxStartRadius{c_maxStartRadius},
        m_maxRadiusMultiplier{c_maxRadiusMultiplier},
        m_spiralSpeed{c_spiralSpeed},
        m_controller{nullptr}
    {}

public:
    static SkySettings& instance()
    {
        static SkySettings instance = SkySettings {};
        return instance;
    }
    SkySettings(SkySettings const&) = delete;
    void operator=(SkySettings const&) = delete;

    int getMaxStars() const {return m_maxStars;}
    void setMaxStars(int maxStars) {m_maxStars = maxStars;}

    double getWidth() const {return m_width;}
    void setWidth(double width) {m_width = width;}

    double getHeight() const {return m_height;}
    void setHeight(double height) {m_height = height;}

    double getMinRadius() const {return m_minRadius;}
    void setMinRadius(double minRadius) {m_minRadius = minRadius;}

    double getMaxRadius() const {return m_maxRadius;}
    void setMaxRadius(double maxRadius) {m_maxRadius = maxRadius;}

    double getRadiusChangeSpeed() const {return m_radiusChangeSpeed;}
    void setRadiusChangeSpeed(double radiusChangeSpeed) {m_radiusChangeSpeed = radiusChangeSpeed;}

    double getMinSpeed() const {return m_minSpeed;}
    void setMinSpeed(double minSpeed) {m_minSpeed = minSpeed;}

    double getMaxSpeed() const {return m_maxSpeed;}
    void setMaxSpeed(double maxSpeed) {m_maxSpeed = maxSpeed;}

    double getMinTargetLenMultiplier() const {return m_minTargetLenMultiplier;}
    void setMinTargetLenMultiplier(double minTargetLenMultiplier) {m_minTargetLenMultiplier = minTargetLenMultiplier;}

    double getMaxTargetLenMultiplier() const {return m_maxTargetLenMultiplier;}
    void setMaxTargetLenMultiplier(double maxTargetLenMultiplier) {m_maxTargetLenMultiplier = maxTargetLenMultiplier;}

    double getMaxStartRadius() const {return m_maxStartRadius;}
    void setMaxStartRadius(double maxStartRadius) {m_maxStartRadius = maxStartRadius;}

    double getMaxRadiusMultiplier() const {return m_maxRadiusMultiplier;}
    void setMaxRadiusMultiplier(double maxRadiusMultiplier) {m_maxRadiusMultiplier = maxRadiusMultiplier;}

    double getSpiralSpeed() const {return m_spiralSpeed;}
    void setSpiralSpeed(const double spiralSpeed) {m_spiralSpeed = spiralSpeed;}

    double convertXToWidgetCoord(double coord, double widgetWidth) const {return coord * widgetWidth / m_width;}
    double convertYToWidgetCoord(double coord, double widgetHeight) const {return coord * widgetHeight / m_height;}

    void setController(std::shared_ptr<SkyController> controller);
};

#endif //SKY_SKYSETTINGS_H

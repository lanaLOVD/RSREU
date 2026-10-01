//
// Created by TheUser on 08.04.2025.
//

#ifndef SKY_SKYOBJECTDRAWING_H
#define SKY_SKYOBJECTDRAWING_H

#include <FL/Fl_Widget.H>
#include "../Sky/SkyObject.h"

class SkyObjectDrawing
{
public:
    virtual void draw(const Fl_Widget& widget, const SkyObject& skyObject) const {};
};


#endif //SKY_SKYOBJECTDRAWING_H

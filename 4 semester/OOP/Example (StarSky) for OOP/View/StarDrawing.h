//
// Created by TheUser on 08.04.2025.
//

#ifndef SKY_STARDRAWING_H
#define SKY_STARDRAWING_H

#include "SkyObjectDrawing.h"

class StarDrawing : public SkyObjectDrawing
{
    void draw(const Fl_Widget& widget, const SkyObject& skyObject) const override;
};


#endif //SKY_STARDRAWING_H

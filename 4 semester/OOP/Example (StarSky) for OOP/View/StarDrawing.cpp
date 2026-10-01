//
// Created by TheUser on 08.04.2025.
//

#include <FL/fl_draw.H>
#include "StarDrawing.h"
#include "../Star/Star.h"
#include "../Sky/SkySettings.h"

void StarDrawing::draw(const Fl_Widget& widget, const SkyObject& skyObject) const
{
    static SkySettings& settings = SkySettings::instance();
    const Star& star = dynamic_cast<const Star&>(skyObject);

    const int x = settings.convertXToWidgetCoord(star.getX() - star.getR(), widget.w());
    const int y = settings.convertXToWidgetCoord(star.getY() - star.getR(), widget.h());
    //fl_draw_circle(x, y, star.getD(), FL_WHITE);
    fl_begin_complex_polygon();
    fl_color(FL_WHITE);
    fl_circle(x, y, star.getR());
    fl_end_complex_polygon();
}
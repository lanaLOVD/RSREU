#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Menu_Bar.H>
#include <FL/Fl_Box.H>

#include "View/StarSkyDrawing.h"
#include "Controller/SkyController.h"
#include "Sky/SkySettings.h"
#include "Sky/MovedSky.h"
#include "Sky/SpiralSky.h"

int main(int argc, char **argv) {
    Fl_Double_Window window = Fl_Double_Window{500, 500, "Stars"};

    Fl_Menu_Bar flMenuBar = Fl_Menu_Bar {0, 0, window.w(), 25};

    StarSkyDrawing starSkyDrawing = StarSkyDrawing {0, 25, window.w(), window.h() - 25};

    int menuIndex = flMenuBar.add("Файл/Выход", FL_COMMAND+'q', [] (Fl_Widget *, void *) {Fl::hide_all_windows();});
    flMenuBar.insert(menuIndex, "Мерцающее звёздное небо", FL_COMMAND+'1', [] (Fl_Widget *w, void *d) {
        StarSkyDrawing* starSkyDrawing = static_cast<StarSkyDrawing*>(d);
        std::shared_ptr<SkyController> controller = std::make_shared<SkyController>(std::make_shared<Sky>(), *starSkyDrawing);
        SkySettings::instance().setController(controller);
        }, &starSkyDrawing);
    flMenuBar.insert(menuIndex + 1, "Двигающееся звёздное небо", FL_COMMAND+'2', [] (Fl_Widget *w, void *d) {
        StarSkyDrawing* starSkyDrawing = static_cast<StarSkyDrawing*>(d);
        std::shared_ptr<SkyController> controller = std::make_shared<SkyController>(std::make_shared<MovedSky>(), *starSkyDrawing);
        SkySettings::instance().setController(controller);
    }, &starSkyDrawing);
    flMenuBar.insert(menuIndex + 2, "Спиральное звёздное небо", FL_COMMAND+'3', [] (Fl_Widget *w, void *d) {
        StarSkyDrawing* starSkyDrawing = static_cast<StarSkyDrawing*>(d);
        std::shared_ptr<SkyController> controller = std::make_shared<SkyController>(std::make_shared<SpiralSky>(), *starSkyDrawing);
        SkySettings::instance().setController(controller);
    }, &starSkyDrawing, FL_MENU_DIVIDER);

    //SkyController skyController = SkyController {new Sky{}, starSkyDrawing};

    window.end();
    window.show(argc, argv);

    return Fl::run();
}
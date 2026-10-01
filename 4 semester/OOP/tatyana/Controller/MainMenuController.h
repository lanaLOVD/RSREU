#ifndef MENU_CONTROLLER_H
#define MENU_CONTROLLER_H

#include <iostream>
#include <memory>
#include <string>

#include <FL/Fl.H>
#include <FL/fl_draw.H>

#include "../View/MainMenuView.h"

#include "GameController.h"
#include "AboutController.h"
#include "AbstractController.h"

class MainMenuController : public AbstractController
{
public:
    MainMenuController(int windowLeft, int windowTop,
                       int windowWidth, int windowHeight,
                       int buttonWidth, int buttonHeight);

    MainMenuController(const MainMenuController&) = delete;

    void run();

    static const int DEFAULT_WINDOW_WIDTH  { 1024 };
    static const int DEFAULT_WINDOW_HEIGHT {  768 };
    static const int DEFAULT_WINDOW_LEFT   {  200 };
    static const int DEFAULT_WINDOW_TOP    {  200 };
    static const int DEFAULT_BUTTON_WIDTH  {  300 };
    static const int DEFAULT_BUTTON_HEIGHT {   80 };

    void takeControl()    override;
    void releaseControl() override;

private:
    AboutController              m_aboutController;
    GameController               m_gameController;
    std::unique_ptr<MainMenuView> m_menuView;
};

#endif
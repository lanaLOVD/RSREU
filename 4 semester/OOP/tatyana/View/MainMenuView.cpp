#include "MainMenuView.h"
#include <iostream>

const std::string MainMenuView::WINDOW_NAME{ "Crossy Road" };

const std::string MainMenuView::MENU_ITEM_TEXT_START_GAME{ "Play" };
const std::string MainMenuView::MENU_ITEM_TEXT_ABOUT{ "Help" };
const std::string MainMenuView::MENU_ITEM_TEXT_EXIT{ "Exit" };

MainMenuView::MainMenuView(int x, int y, int width, int height, int buttonsWidth, int buttonsHeight) :
    Fl_Double_Window(x, y, width, height, WINDOW_NAME.c_str()),
    m_buttonStartGame(x + (width - buttonsWidth) / 2, y + buttonsHeight, buttonsWidth, buttonsHeight, MENU_ITEM_TEXT_START_GAME.c_str()),
    m_buttonAbout(x + (width - buttonsWidth) / 2, y + buttonsHeight * 3, buttonsWidth, buttonsHeight, MENU_ITEM_TEXT_ABOUT.c_str()),
    m_buttonExit(x + (width - buttonsWidth) / 2, y + buttonsHeight * 5, buttonsWidth, buttonsHeight, MENU_ITEM_TEXT_EXIT.c_str())
{
    begin();

    m_buttonStartGame.callback([](Fl_Widget* widget, void* data) {
        auto* view = static_cast<MainMenuView*>(data);
        if (view && view->m_buttonStartGameCallback)
            view->m_buttonStartGameCallback();
    }, this);

    m_buttonAbout.callback([](Fl_Widget* widget, void* data) {
        auto* view = static_cast<MainMenuView*>(data);
        if (view && view->m_buttonAboutCallback)
            view->m_buttonAboutCallback();
    }, this);

    m_buttonExit.callback([](Fl_Widget* widget, void* data) {
        auto* view = static_cast<MainMenuView*>(data);
        if (view && view->m_buttonExitCallback)
            view->m_buttonExitCallback();
    }, this);

    end();
}

// === Реализации setter'ов (были пропущены) ===
void MainMenuView::setButtonStartGameCallback(std::function<void()> callbackFunction)
{
    m_buttonStartGameCallback = std::move(callbackFunction);
}

void MainMenuView::setButtonAboutCallback(std::function<void()> callbackFunction)
{
    m_buttonAboutCallback = std::move(callbackFunction);
}

void MainMenuView::setButtonExitCallback(std::function<void()> callbackFunction)
{
    m_buttonExitCallback = std::move(callbackFunction);
}

void MainMenuView::hideMenu()
{
    m_buttonStartGame.hide();
    m_buttonAbout.hide();
    m_buttonExit.hide();
}

void MainMenuView::showMenu()
{
    m_buttonStartGame.show();
    m_buttonAbout.show();
    m_buttonExit.show();
}

void MainMenuView::show()
{
    std::cout << "MainMenuView::show() called\n";
    Fl_Double_Window::show();
    showMenu();
    take_focus();
    Fl::run();
}
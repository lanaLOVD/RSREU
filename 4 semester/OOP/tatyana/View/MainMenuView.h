#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>

#include <vector>
#include <string>
#include <memory>
#include <functional>

class MainMenuView : public Fl_Double_Window
{
public:
    MainMenuView(int x, int y, int width, int height, int buttonsWidth, int buttonsHeight);

    void hideMenu();
    void showMenu();
    void show() override;

    void setButtonStartGameCallback(std::function<void()> callbackFunction);
    void setButtonAboutCallback(std::function<void()> callbackFunction);
    void setButtonExitCallback(std::function<void()> callbackFunction);

private:
    static const std::string WINDOW_NAME;
    static const std::string MENU_ITEM_TEXT_START_GAME;
    static const std::string MENU_ITEM_TEXT_ABOUT;
    static const std::string MENU_ITEM_TEXT_EXIT;

    Fl_Button m_buttonStartGame;
    Fl_Button m_buttonAbout;
    Fl_Button m_buttonExit;

    std::function<void()> m_buttonStartGameCallback;
    std::function<void()> m_buttonAboutCallback;
    std::function<void()> m_buttonExitCallback;
};

#endif
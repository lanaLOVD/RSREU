#ifndef ABOUT_VIEW_H
#define ABOUT_VIEW_H

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Text_Display.H>

#include <string>
#include <memory>
#include <functional>

#include <iostream>

class AboutView : public Fl_Widget
{
private:
    std::unique_ptr<Fl_Text_Buffer> m_textBuffer;
    std::unique_ptr<Fl_Button> m_buttonBack;
    std::unique_ptr<Fl_Text_Display> m_textDisplay;

    static const std::string BUTTON_TEXT_BACK;

    static const std::string DEVELOPER_INFO;
    static const std::string GAME_HELP;

    std::function<void()> m_buttonBackCallback;

public:
    AboutView(int x, int y, int width, int height, int buttonWidth, int buttonHeight);

    //void hide();

    void show() override;

    void setButtonBackCallback(std::function<void()> callbackFunction);

    void draw() override
    {
        show();
    }
};

#endif
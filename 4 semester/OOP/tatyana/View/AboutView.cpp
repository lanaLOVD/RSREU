#include "AboutView.h"

const std::string AboutView::BUTTON_TEXT_BACK{"Back"};
const std::string AboutView::DEVELOPER_INFO{
    "Developer: Tatyana Ivanova\n\
    Ryazan State Radioengineering Univercity\n\
    Group 4413\n\
    2026\n"};



const std::string AboutView::GAME_HELP{
    "How to play:\n\
    Press arrow keys or wasd to move,\n\
    * arrow up or \'w\' - move forward\n\
    * arrow left or \'a\' - move left\n\
    * arrow right or \'d\' - move right\n\
    NO STEP BACK!\n\
    If you touch a car - you lose.\n\
    Collect as much coins as you can.\n"};


AboutView::AboutView(int x, int y, int width, int height, int buttonWidth, int buttonHeight) :
    Fl_Widget(x, y, width, height),
    m_buttonBack(std::make_unique<Fl_Button>(x + (width - buttonWidth) / 2, y + height - 2 * buttonHeight, buttonWidth, buttonHeight, BUTTON_TEXT_BACK.c_str())),
    m_textDisplay(std::make_unique<Fl_Text_Display>(x + width / 10, y + height / 10, width * 8 / 10, height - 3 * buttonHeight)),
    m_textBuffer(std::make_unique<Fl_Text_Buffer>())
{
    m_textBuffer->append(DEVELOPER_INFO.c_str());
    m_textBuffer->append(GAME_HELP.c_str());

    m_textDisplay->buffer(*m_textBuffer);

    m_buttonBack->callback([](Fl_Widget* widget, void* data)
        {
            AboutView *view{static_cast<AboutView*>(data)};

            if (view->m_buttonBackCallback)
            {
                view->m_buttonBackCallback();
            }
        }, this);
}

//void AboutView::hide()
//{
//    m_textDisplay->hide();
//    m_buttonBack->hide();
//}

void AboutView::show()
{
    std::cout << "about view show\n";

    Fl_Widget::show();

    m_textDisplay->show();
    m_buttonBack->show();
}

void AboutView::setButtonBackCallback(std::function<void()> callbackFunction)
{
    m_buttonBackCallback = callbackFunction;
}
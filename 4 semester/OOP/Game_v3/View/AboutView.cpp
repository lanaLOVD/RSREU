#include "AboutView.h"

/**
* Текст, отображаемый на кнопке возврата в главное меню
*/
const std::string AboutView::BUTTON_TEXT_BACK{"Back"};

/**
* Информация о разработчике
*/
const std::string AboutView::DEVELOPER_INFO{
    "Developer: Tatyana Ivanova\n\
    Ryazan State Radioengineering Univercity\n\
    Group 4413\n\
    2026\n"};


/**
* Игровая справка
*/
const std::string AboutView::GAME_HELP{
    "How to play:\n\
    Press arrow keys or wasd to move,\n\
    * arrow up or \'w\' - move forward\n\
    * arrow left or \'a\' - move left\n\
    * arrow right or \'d\' - move right\n\
    NO STEP BACK!\n\
    If you touch a car - you lose.\n\
    Collect as much coins as you can.\n"};

/**
* Коструктор
* int width - ширина окна в пикселях
* int height - высота окна в пикселях
* int buttonWidth - ширина кнопки в пикселях
* int buttonHeight - высота кнопки в пикселях
*/
AboutView::AboutView(int width, int height, int buttonWidth, int buttonHeight) :
    Fl_Double_Window(width, height),
    m_buttonBack((width - buttonWidth) / 2, height - 2 * buttonHeight, buttonWidth, buttonHeight, BUTTON_TEXT_BACK.c_str()),
    m_textDisplay(width / TEXT_DISPLAY_RATIO, height / TEXT_DISPLAY_RATIO, width * TEXT_DISPLAY_LENGTH_MULTIPLIER / TEXT_DISPLAY_RATIO, height - 3 * buttonHeight)
{
    m_textBuffer.append(DEVELOPER_INFO.c_str());
    m_textBuffer.append(GAME_HELP.c_str());

    m_textDisplay.buffer(m_textBuffer);

    m_buttonBack.callback([](Fl_Widget* widget, void* data)
        {
            AboutView *view{static_cast<AboutView*>(data)};

            if (view->m_buttonBackCallback)
            {
                view->m_buttonBackCallback();
            }
        }, this);
}

/**
* Установка обратного вызова для кнопки возврата в главное меню
* std::function<void()> callbackFunction - обратный вызов
*/
void AboutView::setButtonBackCallback(std::function<void()> callbackFunction)
{
    m_buttonBackCallback = callbackFunction;
}
#include "MainMenuView.h"

/**
* Заголовок окна
*/
const std::string MainMenuView::WINDOW_NAME{ "Crossy Road" };

/**
* Текст на кнопке начала игры
*/
const std::string MainMenuView::MENU_ITEM_TEXT_START_GAME{ "Play" };

/**
* Текст на кнопке справки
*/
const std::string MainMenuView::MENU_ITEM_TEXT_ABOUT{ "Help" };

/**
* Текст на кнопке выхода
*/
const std::string MainMenuView::MENU_ITEM_TEXT_EXIT{ "Exit" };

/**
* Реализация конструктора
* int width - ширина окна
* int height - высота окна
* int buttonsWidth - ширина кнопок
* int buttonsHeight - высота кнопок
*/
MainMenuView::MainMenuView(int width, int height, int buttonsWidth, int buttonsHeight) :
    Fl_Double_Window(width, height, WINDOW_NAME.c_str()),
    m_buttonStartGame((width - buttonsWidth) / 2, buttonsHeight, buttonsWidth, buttonsHeight, MENU_ITEM_TEXT_START_GAME.c_str()),
    m_buttonAbout((width - buttonsWidth) / 2, buttonsHeight * 3, buttonsWidth, buttonsHeight, MENU_ITEM_TEXT_ABOUT.c_str()),
    m_buttonExit((width - buttonsWidth) / 2, buttonsHeight * 5, buttonsWidth, buttonsHeight, MENU_ITEM_TEXT_EXIT.c_str())
{
    begin();

    position(0, 0);

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

/**
* Установка обратного вызова для кнопки начала игры
* std::function<void()> callbackFunction - обратный вызов
*/
void MainMenuView::setButtonStartGameCallback(std::function<void()> callbackFunction)
{
    m_buttonStartGameCallback = callbackFunction;
}

/**
* Установка обратного вызова для кнопки просмотра справки
* std::function<void()> callbackFunction - обратный вызов
*/
void MainMenuView::setButtonAboutCallback(std::function<void()> callbackFunction)
{
    m_buttonAboutCallback = callbackFunction;
}

/**
* Установка обратного вызова для кнопки выхода
* std::function<void()> callbackFunction - обратный вызов
*/
void MainMenuView::setButtonExitCallback(std::function<void()> callbackFunction)
{
    m_buttonExitCallback = callbackFunction;
}

/**
* Отображение окна и запуск цикла обработки событий
*/
void MainMenuView::display()
{
    show();
    Fl::run();
}
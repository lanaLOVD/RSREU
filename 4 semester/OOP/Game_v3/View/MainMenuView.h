#ifndef MENU_VIEW_H
#define MENU_VIEW_H

#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>

#include <vector>
#include <string>
#include <functional>

/**
 * Отображение главного меню
 */
class MainMenuView : public Fl_Double_Window
{
public:
    /**
     * Конструктор
     * int width - ширина окна
     * int height - высота окна
     * int buttonsWidth - ширина кнопок
     * int buttonsHeight - высота кнопок
     */
    MainMenuView(int width, int height, int buttonsWidth, int buttonsHeight);

    /**
     * Отображение окна и запуск цикла обработки событий
     */
    void display();

    /**
     * Установка обратного вызова для кнопки начала игры
     * std::function<void()> callbackFunction - обратный вызов
     */
    void setButtonStartGameCallback(std::function<void()> callbackFunction);

    /**
     * Установка обратного вызова для кнопки просмотра справки
     * std::function<void()> callbackFunction - обратный вызов
     */
    void setButtonAboutCallback(std::function<void()> callbackFunction);

    /**
     * Установка обратного вызова для кнопки выхода
     * std::function<void()> callbackFunction - обратный вызов
     */
    void setButtonExitCallback(std::function<void()> callbackFunction);

private:
    /**
     * Заголовок окна
     */
    static const std::string WINDOW_NAME;

    /**
     * Текст на кнопке начала игры
     */
    static const std::string MENU_ITEM_TEXT_START_GAME;

    /**
     * Текст на кнопке справки
     */
    static const std::string MENU_ITEM_TEXT_ABOUT;

    /**
     * Текст на кнопке выхода
     */
    static const std::string MENU_ITEM_TEXT_EXIT;

    /**
     * Кнопка начала игры
     */
    Fl_Button m_buttonStartGame;

    /**
     * Кнопка просмотра справки
     */
    Fl_Button m_buttonAbout;

    /**
     * Кнопка выхода
     */
    Fl_Button m_buttonExit;

    /**
     * Обратный вызов для кнопки начала игры
     */
    std::function<void()> m_buttonStartGameCallback;

    /**
     * Обратный вызов для кнопки просмотра справки
     */
    std::function<void()> m_buttonAboutCallback;

    /**
     * Обратный вызов для кнопки выхода
     */
    std::function<void()> m_buttonExitCallback;
};

#endif
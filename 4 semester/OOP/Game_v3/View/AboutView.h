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

/**
 * Отображение окна справки
 */
class AboutView : public Fl_Double_Window
{
private:
    /**
     * Буфер, содержащий текст справки
     */
    Fl_Text_Buffer m_textBuffer;

    /**
     * Кнопка возврата в гланое меню
     */
    Fl_Button m_buttonBack;

    /**
     * Виджет для отображения текста
     */
    Fl_Text_Display m_textDisplay;

    /**
     * Текст, отображаемый на кнопке возврата в главное меню
     */
    static const std::string BUTTON_TEXT_BACK;

    /**
     * Информация о разработчике
     */
    static const std::string DEVELOPER_INFO;

    /**
     * Игровая справка
     */
    static const std::string GAME_HELP;

    /**
     * Обратный вызов для кнопки возврата в главное меню
     */
    std::function<void()> m_buttonBackCallback;

    /**
     * Множитель для ширины текстового поля
     */
    static const int TEXT_DISPLAY_LENGTH_MULTIPLIER{ 8 };

    /**
     * Делитель для ширины текстового поля
     */
    static const int TEXT_DISPLAY_RATIO{ 10 };

public:
    /**
     * Коструктор
     * int width - ширина окна в пикселях
     * int height - высота окна в пикселях
     * int buttonWidth - ширина кнопки в пикселях
     * int buttonHeight - высота кнопки в пикселях
     */
    AboutView(int width, int height, int buttonWidth, int buttonHeight);

    /**
     * Установка обратного вызова для кнопки возврата в главное меню
     * std::function<void()> callbackFunction - обратный вызов
     */
    void setButtonBackCallback(std::function<void()> callbackFunction);

};

#endif
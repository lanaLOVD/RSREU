#pragma once

#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.H>
#include <string>
#include <vector>
#include <functional>

/**
 * @brief Окно "О программе" с описанием управления и кнопкой OK.
 */
class AboutWindow : public Fl_Double_Window {
private:
    /// @brief Кнопка закрытия окна
    Fl_Button* m_okButton;

    /// @brief Строки с описанием управления
    std::vector<std::string> m_controlLines;

    /// @brief Callback, вызываемый при закрытии окна (устанавливается контроллером)
    std::function<void()> m_closeCallback;

    /**
     * @brief Статический обработчик нажатия кнопки OK для FLTK.
     * @param widget  Виджет-источник события
     * @param data    Указатель на экземпляр AboutWindow
     */
    static void onOkButtonClicked(Fl_Widget* widget, void* data);

public:
    /**
     * @brief Конструктор окна "О программе".
     * @param width   Ширина окна
     * @param height  Высота окна
     * @param title   Заголовок окна
     */
    AboutWindow(int width, int height, const char* title);

    /** @brief Деструктор */
    ~AboutWindow();

    /** @brief Отрисовывает содержимое окна */
    void draw() override;

    /**
     * @brief Устанавливает callback, вызываемый при нажатии OK.
     * @param callback  Функция без аргументов
     */
    void setCloseCallback(std::function<void()> callback);
};

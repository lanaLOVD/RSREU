#pragma once

#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Button.H>
#include <string>
#include <vector>
#include <functional>
#include <memory>

/**
 * @brief Окно "О программе" с описанием управления и кнопкой OK.
 *
 * Отображает справку по управлению игрой.
 * При нажатии кнопки OK вызывает m_closeCallback (если установлен) и скрывает окно.
 */
class AboutWindow : public Fl_Double_Window {
private:
    /// @brief Кнопка закрытия окна (не владеет памятью — FLTK управляет виджетами)
    Fl_Button* m_okButton;

    /// @brief Строки с описанием управления, выводимые в окне
    std::vector<std::string> m_controlLines;

    /// @brief Callback, вызываемый при нажатии кнопки OK (устанавливается контроллером)
    std::function<void()> m_closeCallback;

    /**
     * @brief Статический обработчик нажатия кнопки OK для FLTK.
     *
     * FLTK требует статическую функцию; получает экземпляр через параметр data.
     *
     * @param widget  Виджет-источник события (не используется)
     * @param data    Указатель на экземпляр AboutWindow
     */
    static void onOkButtonClicked(Fl_Widget* widget, void* data);

public:
    /**
     * @brief Конструктор окна "О программе".
     *
     * Создаёт окно с текстом управления и кнопкой OK.
     *
     * @param width   Ширина окна в пикселях
     * @param height  Высота окна в пикселях
     * @param title   Заголовок окна
     */
    AboutWindow(int width, int height, const char* title);

    /**
     * @brief Деструктор.
     */
    ~AboutWindow();

    /**
     * @brief Отрисовывает содержимое окна: заголовок, разделитель, строки управления.
     */
    void draw() override;

    /**
     * @brief Устанавливает callback, вызываемый при нажатии кнопки OK.
     * @param callback  Функция без аргументов, вызываемая при закрытии окна
     */
    void setCloseCallback(std::function<void()> callback);
};
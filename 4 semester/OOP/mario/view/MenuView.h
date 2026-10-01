#pragma once
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <memory>
#include <functional>

/**
 * @brief Главное меню игры.
 *
 * Содержит три кнопки: New Game, About, Exit.
 * Действия передаются через callback-и, устанавливаемые контроллером.
 * View не знает ничего о контроллере.
 */
class MenuView : public Fl_Window {
private:
    /// @brief Кнопка запуска новой игры
    std::unique_ptr<Fl_Button> m_newGameBtn;

    /// @brief Кнопка открытия окна "О программе"
    std::unique_ptr<Fl_Button> m_aboutBtn;

    /// @brief Кнопка выхода из приложения
    std::unique_ptr<Fl_Button> m_exitBtn;

    /// @brief Callback для кнопки "New Game"
    std::function<void()> m_startGameCallback;

    /// @brief Callback для кнопки "About"
    std::function<void()> m_aboutCallback;

    /// @brief Callback для кнопки "Exit"
    std::function<void()> m_exitCallback;

public:
    /**
     * @brief Конструктор главного меню.
     * @param w      Ширина окна
     * @param h      Высота окна
     * @param title  Заголовок окна
     */
    MenuView(int w, int h, const char* title);

    /**
     * @brief Устанавливает callback для кнопки "New Game".
     * @param callback  Функция без аргументов
     */
    void setCallBackNewGame(std::function<void()> callback);

    /**
     * @brief Устанавливает callback для кнопки "About".
     * @param callback  Функция без аргументов
     */
    void setCallBackAbout(std::function<void()> callback);

    /**
     * @brief Устанавливает callback для кнопки "Exit".
     * @param callback  Функция без аргументов
     */
    void setCallBackExit(std::function<void()> callback);
};

#pragma once

#include <memory>
#include "../view/MenuView.h"

class GameController;
class AboutController;

/**
 * @brief Главный контроллер меню.
 *
 * Создаёт все контроллеры приложения (GameController, AboutController)
 * и MenuView. Связывает кнопки меню с соответствующими действиями через callback-и.
 */
class MenuController {
private:
    /// @brief Вид главного меню
    std::unique_ptr<MenuView> m_menuView;

    /// @brief Контроллер игрового процесса
    std::unique_ptr<GameController> m_gameController;

    /// @brief Контроллер окна "О программе"
    std::unique_ptr<AboutController> m_aboutController;

    /**
     * @brief Регистрирует callback-и кнопок MenuView.
     */
    void setupCallBacks();

public:
    /** @brief Конструктор: создаёт все дочерние контроллеры и вид */
    MenuController();

    /** @brief Показывает главное меню */
    void run();
};

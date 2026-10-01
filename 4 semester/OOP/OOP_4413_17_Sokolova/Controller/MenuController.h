#pragma once

#include <memory>
#include "../view/MenuView.h"
#include "GameController.h"
#include "AboutController.h"

/**
 * @brief Главный контроллер меню.
 *
 * Создаёт все контроллеры приложения (GameController, AboutController)
 * и MenuView. Связывает кнопки меню с соответствующими действиями через callback-и.
 * Не содержит игровой логики.
 */
class MenuController : public std::enable_shared_from_this<MenuController> {
private:
    /// @brief Вид главного меню (владеет)
    std::unique_ptr<MenuView> m_menuView;

    /// @brief Контроллер игрового процесса (владеет)
    std::unique_ptr<GameController> m_gameController;

    /// @brief Контроллер окна "О программе" (владеет)
    std::unique_ptr<AboutController> m_aboutController;

    /**
     * @brief Регистрирует callback-и кнопок MenuView.
     */
    void setupCallBacks();

public:
    /**
     * @brief Конструктор: создаёт все дочерние контроллеры и вид меню.
     */
    MenuController();

    /**
     * @brief Инициализирует связи между контроллерами.
     *
     * Должен вызываться сразу после создания shared_ptr на MenuController.
     */
    void init();

    /**
     * @brief Показывает главное меню.
     */
    void run();
};
#pragma once

#include <memory>
#include "../view/AboutWindow.h"

class MenuController;

/**
 * @brief Контроллер окна "О программе".
 *
 * Создаёт AboutWindow и показывает его по запросу.
 * Взаимодействует с MenuController через std::weak_ptr.
 */
class AboutController {
private:
    /// @brief Окно "О программе" (владеет)
    std::unique_ptr<AboutWindow> m_aboutWindow;

    /// @brief Слабая ссылка на контроллер меню (не владеет)
    std::weak_ptr<MenuController> m_menuController;

public:
    /**
     * @brief Конструктор: создаёт экземпляр AboutWindow.
     */
    AboutController();

    /**
     * @brief Показывает окно "О программе".
     */
    void run();

    /**
     * @brief Устанавливает слабую ссылку на MenuController.
     * @param menu  shared_ptr на MenuController
     */
    void setMenuController(std::shared_ptr<MenuController> menu);
};
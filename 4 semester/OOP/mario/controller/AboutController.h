#pragma once

#include <memory>
#include "../view/AboutWindow.h"

class MenuController;

/**
 * @brief Контроллер окна "О программе".
 *
 * Создаёт AboutWindow и показывает его по запросу.
 * Взаимодействует с MenuController через указатель.
 */
class AboutController {
private:
    /// @brief Окно "О программе"
    std::unique_ptr<AboutWindow> m_aboutWindow;

    /// @brief Указатель на контроллер меню (не владеет)
    MenuController* m_menuController;

public:
    /** @brief Конструктор: создаёт AboutWindow */
    AboutController();

    /** @brief Показывает окно "О программе" */
    void run();

    /**
     * @brief Устанавливает указатель на MenuController.
     * @param menu  Указатель на MenuController
     */
    void setMenuController(MenuController* menu);
};

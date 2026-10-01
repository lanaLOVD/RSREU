#include "AboutController.h"

/**
 * @brief Конструктор: создаёт окно AboutWindow.
 */
AboutController::AboutController()
    : m_aboutWindow{ std::make_unique<AboutWindow>(400, 400, "About Mario Game") },
      m_menuController{ nullptr } {
}

/**
 * @brief Показывает окно "О программе".
 */
void AboutController::run() {
    m_aboutWindow->show();
}

/**
 * @brief Устанавливает указатель на MenuController.
 * @param menu  Указатель на MenuController
 */
void AboutController::setMenuController(MenuController* menu) {
    m_menuController = menu;
}

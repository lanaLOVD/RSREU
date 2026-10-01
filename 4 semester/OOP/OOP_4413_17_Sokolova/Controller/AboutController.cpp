#include "AboutController.h"

/**
 * @brief Конструктор: создаёт окно AboutWindow.
 */
AboutController::AboutController()
    : m_aboutWindow{ std::make_unique<AboutWindow>(400, 400, "About Mario Game") },
      m_menuController{} {
}

/**
 * @brief Показывает окно "О программе".
 */
void AboutController::run() {
    m_aboutWindow->show();
}

/**
 * @brief Устанавливает слабую ссылку на MenuController.
 * @param menu  shared_ptr на MenuController
 */
void AboutController::setMenuController(std::shared_ptr<MenuController> menu) {
    m_menuController = menu;
}
#include "MenuController.h"
#include "../controller/GameController.h"
#include "../controller/AboutController.h"

/**
 * @brief Конструктор: создаёт GameController, AboutController и MenuView.
 *
 * Передаёт ссылку на себя в GameController для возврата в меню после конца игры.
 */
MenuController::MenuController()
    : m_menuView     { std::make_unique<MenuView>(400, 300, "Mario Game") },
      m_gameController { std::make_unique<GameController>(1200, 600) },
      m_aboutController{ std::make_unique<AboutController>() } {

    m_gameController->setMenuController(this);
}

/**
 * @brief Регистрирует callback-и для трёх кнопок MenuView.
 *
 * Контроллер устанавливает лямбды через setCallBack*, View не знает о контроллере.
 */
void MenuController::setupCallBacks() {
    m_menuView->setCallBackNewGame([this]() {
        m_menuView->hide();
        m_gameController->run();
    });

    m_menuView->setCallBackAbout([this]() {
        m_aboutController->run();
    });

    m_menuView->setCallBackExit([this]() {
        exit(0);
    });
}

/**
 * @brief Показывает главное меню.
 */
void MenuController::run() {
    setupCallBacks();
    m_menuView->show();
}

#include "MenuController.h"
#include "../controller/GameController.h"
#include "../controller/AboutController.h"

/**
 * @brief Конструктор: создаёт GameController, AboutController и MenuView.
 */
MenuController::MenuController()
    : m_menuView      { std::make_unique<MenuView>(400, 300, "Mario Game") },
      m_gameController { std::make_unique<GameController>(1200, 600) },
      m_aboutController{ std::make_unique<AboutController>() } {
}

/**
 * @brief Инициализирует связи между контроллерами через shared_from_this.
 *
 * Вызывается после создания shared_ptr на MenuController в main().
 */
void MenuController::init() {
    m_gameController->setMenuController(shared_from_this());
    m_aboutController->setMenuController(shared_from_this());
}

/**
 * @brief Регистрирует callback-и для трёх кнопок MenuView.
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
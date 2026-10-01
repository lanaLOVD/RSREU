#include "GameController.h"
#include "../controller/MenuController.h"

/**
 * @brief Конструктор: создаёт GameModel и GameView, регистрирует callback-и клавиш.
 * @param width   Ширина игрового окна
 * @param height  Высота игрового окна
 */
GameController::GameController(int width, int height)
    : m_isGameActive{ false }, m_menuController{ nullptr },
      m_keyLeft{ false }, m_keyRight{ false }, m_keySpace{ false } {

    m_model = std::make_unique<GameModel>();
    m_view  = std::make_unique<GameView>(width, height, "Mario", m_model.get());

    // Передаём обработчики клавиш через callback-и — View не знает о контроллере
    m_view->setKeyDownCallback([this](int key) { handleKeyDown(key); });
    m_view->setKeyUpCallback  ([this](int key) { handleKeyUp(key);   });
}

/**
 * @brief Деструктор: освобождает ресурсы.
 */
GameController::~GameController() {
    cleanUp();
}

/**
 * @brief Останавливает таймер, модель и скрывает окно.
 */
void GameController::cleanUp() {
    Fl::remove_timeout(timerCallback, this);

    if (m_isGameActive && m_model) {
        m_model->stop();
    }

    m_isGameActive = false;

    if (m_view) {
        m_view->hide();
    }
}

/**
 * @brief Запускает игру: сбрасывает модель, показывает окно, запускает таймер.
 */
void GameController::run() {
    if (!m_model || !m_view) {
        return;
    }

    cleanUp();

    m_isGameActive = true;
    m_view->show();

    m_model->reset();
    m_model->start();

    m_keyLeft  = false;
    m_keyRight = false;
    m_keySpace = false;

    Fl::add_timeout(1.0 / 60.0, timerCallback, this);
}

/**
 * @brief Скрывает игровое окно и открывает меню.
 */
void GameController::returnToMenu() {
    cleanUp();

    if (m_menuController) {
        m_menuController->run();
    }
}

/**
 * @brief Тик игрового цикла: проверяет конец игры или передаёт ввод в модель.
 * @param data  Указатель на GameController
 */
void GameController::timerCallback(void* data) {
    GameController* controller = static_cast<GameController*>(data);

    if (!controller || !controller->m_model) {
        return;
    }

    if (controller->m_isGameActive) {
        if (controller->m_model->getGameOver()) {
            controller->returnToMenu();
        } else {
            controller->processInput();
            Fl::repeat_timeout(1.0 / 60.0, timerCallback, data);
        }
    }
}

/**
 * @brief Обрабатывает нажатие клавиши — обновляет флаг состояния.
 * @param key  Код клавиши FLTK
 */
void GameController::handleKeyDown(int key) {
    switch (key) {
    case FL_Left:  m_keyLeft  = true; break;
    case FL_Right: m_keyRight = true; break;
    case ' ':      m_keySpace = true; break;
    }
}

/**
 * @brief Обрабатывает отпускание клавиши — сбрасывает флаг состояния.
 * @param key  Код клавиши FLTK
 */
void GameController::handleKeyUp(int key) {
    switch (key) {
    case FL_Left:  m_keyLeft  = false; break;
    case FL_Right: m_keyRight = false; break;
    case ' ':      m_keySpace = false; break;
    }
}

/**
 * @brief Передаёт текущие флаги клавиш в методы игрока модели.
 */
void GameController::processInput() {
    if (!m_model || !m_model->getPlayer()) return;

    m_model->getPlayer()->stop();

    if (m_keyLeft)  m_model->getPlayer()->moveLeft();
    if (m_keyRight) m_model->getPlayer()->moveRight();
    if (m_keySpace) m_model->getPlayer()->jump();
}

/**
 * @brief Устанавливает ссылку на MenuController.
 * @param menu  Указатель на MenuController
 */
void GameController::setMenuController(MenuController* menu) {
    m_menuController = menu;
}

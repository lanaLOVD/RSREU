#include "GameController.h"
#include "../controller/MenuController.h"

/**
 * @brief Конструктор.
 */
GameController::GameController(int width, int height)
    : m_isGameActive{ false }
    , m_menuController{}
    , m_keyLeft{ false }
    , m_keyRight{ false }
    , m_keySpace{ false }
    , m_model{ std::make_unique<GameModel>() }
{
    m_view = std::make_unique<GameView>(width, height, "Mario", *m_model);

    m_view->setKeyDownCallback([this](int key){ handleKeyDown(key); });
    m_view->setKeyUpCallback  ([this](int key){ handleKeyUp(key); });
}

GameController::~GameController() {
    cleanUp();
}

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

void GameController::run() {
    if (!m_model || !m_view) return;

    cleanUp();

    m_isGameActive = true;
    m_view->show();

    m_model->reset();
    m_model->start();

    m_keyLeft = false;
    m_keyRight = false;
    m_keySpace = false;

    Fl::add_timeout(1.0 / 60.0, timerCallback, this);
}

void GameController::returnToMenu() {
    cleanUp();

    if (auto menu = m_menuController.lock()) {
        menu->run();
    }
}

/**
 * Таймер — теперь максимально надёжный
 */
void GameController::timerCallback(void* data) {
    GameController* ctrl = static_cast<GameController*>(data);
    if (!ctrl || !ctrl->m_isGameActive) return;

    // Если игра окончена — сразу закрываем окно
    if (ctrl->m_model && ctrl->m_model->getGameOver()) {
        Fl::remove_timeout(timerCallback, data);

        // Немного показываем GAME OVER и возвращаемся в меню
        Fl::add_timeout(1.0, [](void* d) {
            GameController* c = static_cast<GameController*>(d);
            if (c) c->returnToMenu();
        }, ctrl);

        return;
    }

    // Обычный режим игры
    ctrl->processInput();
    Fl::repeat_timeout(1.0 / 60.0, timerCallback, data);
}

void GameController::handleKeyDown(int key) {
    if (!m_model || m_model->getGameOver()) return;

    switch (key) {
        case FL_Left:  case 'a': m_keyLeft  = true; break;
        case FL_Right: case 'd': m_keyRight = true; break;
        case 'w':      case ' ': m_keySpace = true; break;
        default: break;
    }
}

void GameController::handleKeyUp(int key) {
    switch (key) {
        case FL_Left:  case 'a': m_keyLeft  = false; break;
        case FL_Right: case 'd': m_keyRight = false; break;
        case 'w':      case ' ': m_keySpace = false; break;
        default: break;
    }
}

void GameController::processInput() {
    if (!m_model || m_model->getGameOver()) return;

    bool isRunning{ static_cast<bool>(Fl::event_state(FL_SHIFT)) };
    m_model->handleInput(m_keyLeft, m_keyRight, m_keySpace, isRunning);
}

void GameController::setMenuController(std::shared_ptr<MenuController> menu) {
    m_menuController = std::move(menu);
}
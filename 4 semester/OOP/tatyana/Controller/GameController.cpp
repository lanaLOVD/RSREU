#include "GameController.h"
#include <FL/Fl.H>

GameController::GameController(int x, int y, int width, int height, AbstractController* parent)
    : AbstractController(parent)
    , m_game(Game::getInstance())
    , m_gameView(std::make_unique<GameView>(x, y, width, height))
{
    // Клавиши управления
    m_gameView->setKeyCallback([this](int key)
    {
        handleKeyPress(key);
    });

    // Выход из игры обратно в меню
    m_gameView->setExitCallback([this]()
    {
        releaseControl();
        if (getParent())
            getParent()->takeControl();
    });
}

void GameController::handleKeyPress(int key)
{
    switch (key)
    {
        case FL_Up:
        case 'w':
        case 'W':
            m_game.movePlayerForward();
            break;

        case FL_Left:
        case 'a':
        case 'A':
            m_game.movePlayerLeft();
            break;

        case FL_Right:
        case 'd':
        case 'D':
            m_game.movePlayerRight();
            break;

        default:
            break;
    }

    m_gameView->refresh();
}

void GameController::takeControl()
{
    m_game.initGame();
    m_game.startGame();
    m_gameView->show();
}

void GameController::releaseControl()
{
    m_game.stopGame();
    m_gameView->stopTimer();
    m_gameView->hide();
}
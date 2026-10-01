#include "GameController.h"
#include <FL/Fl.H>

/**
* Реализация конструктора
* int width - ширина окна
* int height - высота окна
* AbstractController* parent - главный контроллер
*/
GameController::GameController(int width, int height, AbstractController* parent)
    : AbstractController(parent)
    , m_rGame(Game::getInstance())
    , m_gameView(std::make_unique<GameView>(width, height))
{
    m_gameView->setMoveForwardCallback([this]()
        {
            m_rGame.movePlayerForward();
            m_gameView->refresh();
        });

    m_gameView->setMoveLeftCallback([this]()
        {
            m_rGame.movePlayerLeft();
            m_gameView->refresh();
        });

    m_gameView->setMoveRightCallback([this]()
        {
            m_rGame.movePlayerRight();
            m_gameView->refresh();
        });


    m_gameView->setExitCallback([this]()
    {
        releaseControl();
        if (getParent())
            getParent()->takeControl();
    });
}

/**
* Получение управления
*/
void GameController::takeControl()
{
    m_rGame.initGame();
    m_rGame.startGame();
    m_gameView->show();
}

/**
* Завершение управления
*/
void GameController::releaseControl()
{
    m_rGame.stopGame();
    m_gameView->stopTimer();
    m_gameView->hide();
}
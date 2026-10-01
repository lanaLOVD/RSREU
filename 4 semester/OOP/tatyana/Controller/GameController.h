#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <memory>
#include <FL/Fl.H>

#include "AbstractController.h"
#include "../Model/Game.h"
#include "../View/GameView.h"

class GameController : public AbstractController
{
private:
    Game&                     m_game;
    std::unique_ptr<GameView> m_gameView;

    void handleKeyPress(int key);

public:
    GameController(const GameController&) = delete;

    GameController(int x, int y, int width, int height, AbstractController* parent);

    void takeControl()    override;
    void releaseControl() override;
};

#endif
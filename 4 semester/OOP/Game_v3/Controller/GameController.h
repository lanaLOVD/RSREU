#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <memory>

#include "AbstractController.h"
#include "../Model/Game.h"
#include "../View/GameView.h"

/**
 * Контроллер для окна игры
 */
class GameController : public AbstractController
{
private:
    /**
     * Ссылка на объект, содержащий игровую логику
     */
    Game& m_rGame;

    /**
     * Указатель на отображение окна игры
     */
    std::unique_ptr<GameView> m_gameView;

public:
    /**
    * Конструктор копирования удалён
    */
    GameController(const GameController&) = delete;

    /**
     * Конструктор
     * int width - ширина окна
     * int height - высота окна
     * AbstractController* parent - главный контроллер
     */
    GameController(int width, int height, AbstractController* parent);

    /**
     * Получение управления
     */
    void takeControl() override;

    /**
     * Завершение управления
     */
    void releaseControl() override;
};

#endif
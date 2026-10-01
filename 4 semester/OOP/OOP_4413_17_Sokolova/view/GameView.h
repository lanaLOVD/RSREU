#pragma once

#include <FL/Fl_Double_Window.H>
#include <FL/fl_draw.H>
#include <FL/Fl.H>
#include <functional>
#include "../model/GameModel.h"

/**
 * @brief Игровое окно — отрисовывает мир и передаёт события клавиатуры через callback-и.
 *
 * View НЕ знает ничего про контроллеры.
 */
class GameView : public Fl_Double_Window {
private:
    /// @brief Ссылка на игровую модель (не владеет)
    GameModel& m_model;

    /// @brief Callback для нажатия клавиши
    std::function<void(int)> m_keyDownCallback;

    /// @brief Callback для отпускания клавиши
    std::function<void(int)> m_keyUpCallback;

    static void timerCallback(void* data);

    int handle(int event) override;

    void drawPlatforms();
    void drawPlatform(double x, double y, double width, double height);
    void drawBackground();
    void drawClouds();
    void drawCloud(double x, double y, double size);
    void drawEnemies();
    void drawEnemy(double x, double y, double width, double height);
    void drawCoins();
    void drawCoin(double x, double y, double width, double height, double rotation);
    void drawPlayer();
    void drawPlayerCharacter(double x, double y, double width, double height);
    void drawUI();

public:
    /**
     * @brief Конструктор игрового окна.
     */
    GameView(int width, int height, const char* title, GameModel& model)
        : Fl_Double_Window{ width, height, title }
    , m_model{ model }
    {
        Fl::add_timeout(1.0 / 60.0, timerCallback, this);
    }

    void setKeyDownCallback(std::function<void(int)> cb) {
        m_keyDownCallback = std::move(cb);
    }

    void setKeyUpCallback(std::function<void(int)> cb) {
        m_keyUpCallback = std::move(cb);
    }

    void draw() override;
};
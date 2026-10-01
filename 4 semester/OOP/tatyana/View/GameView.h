#ifndef GAME_VIEW_H
#define GAME_VIEW_H

#include <FL/Fl_Widget.H>
#include <FL/Fl.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/fl_draw.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Button.H>

#include <string>
#include <functional>
#include <memory>
#include <iostream>

#include "../Model/Game.h"
#include "../Model/GameConstants.h"

class GameView : public Fl_Double_Window
{
private:
    Game& m_game;

    double m_timeout;
    bool m_hasTimeout;

    std::function<void(int)> m_keyCallback;
    std::function<void()>    m_exitCallback;

    std::unique_ptr<Fl_PNG_Image> m_imgChicken;
    std::unique_ptr<Fl_PNG_Image> m_imgGreenCar;
    std::unique_ptr<Fl_PNG_Image> m_imgOrangeCar;
    std::unique_ptr<Fl_PNG_Image> m_imgTruck;
    std::unique_ptr<Fl_PNG_Image> m_imgCoin;
    std::unique_ptr<Fl_PNG_Image> m_imgRoad;
    std::unique_ptr<Fl_PNG_Image> m_imgRoadside;

    static const std::string WINDOW_NAME;
    static const std::string IMG_PATH_CHICKEN;
    static const std::string IMG_PATH_GREEN_CAR;
    static const std::string IMG_PATH_ORANGE_CAR;
    static const std::string IMG_PATH_TRUCK;
    static const std::string IMG_PATH_COIN;
    static const std::string IMG_PATH_ROAD;
    static const std::string IMG_PATH_ROADSIDE;

    static void timerCallback(void* data);

    void drawBackground()  const;
    void drawLanes()       const;
    void drawVehicles()    const;
    void drawCoins()       const;
    void drawPlayer()      const;
    void drawHUD()         const;
    void drawGameOver()    const;

    // Вспомогательный метод: игровые координаты → пиксели
    int gameXtoScreen(double gameX) const;
    int laneYtoScreen(int laneIndex) const;
    int laneHeightPx() const;

public:
    GameView(int x, int y, int width, int height);
    ~GameView() override;

    void show() override;
    void draw() override;
    int  handle(int event) override;

    void startTimer();
    void stopTimer();
    void refresh();

    void setKeyCallback(std::function<void(int)> cb) { m_keyCallback = cb; }
    void setExitCallback(std::function<void()>   cb) { m_exitCallback = cb; }
};

#endif
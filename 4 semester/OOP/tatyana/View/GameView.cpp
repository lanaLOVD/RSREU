#include "GameView.h"

const std::string GameView::WINDOW_NAME     { "Crossy Road" };
const std::string GameView::IMG_PATH_CHICKEN    { "Resources/chicken.png"     };
const std::string GameView::IMG_PATH_GREEN_CAR  { "Resources/green_car.png"   };
const std::string GameView::IMG_PATH_ORANGE_CAR { "Resources/orange_car.png"  };
const std::string GameView::IMG_PATH_TRUCK      { "Resources/cargo_truck.png" };
const std::string GameView::IMG_PATH_COIN       { "Resources/coin.png"        };
const std::string GameView::IMG_PATH_ROAD       { "Resources/lane_road.png"   };
const std::string GameView::IMG_PATH_ROADSIDE   { "Resources/lane_roadside.png" };

GameView::GameView(int x, int y, int width, int height)
    : Fl_Double_Window(x, y, width, height, WINDOW_NAME.c_str())
    , m_game(Game::getInstance())
    , m_timeout(1.0 / 60.0)
    , m_hasTimeout(false)
{
    auto tryLoad = [](const std::string& path) -> std::unique_ptr<Fl_PNG_Image>
    {
        auto img = std::make_unique<Fl_PNG_Image>(path.c_str());
        if (img->fail()) return nullptr;
        return img;
    };

    m_imgChicken    = tryLoad(IMG_PATH_CHICKEN);
    m_imgGreenCar   = tryLoad(IMG_PATH_GREEN_CAR);
    m_imgOrangeCar  = tryLoad(IMG_PATH_ORANGE_CAR);
    m_imgTruck      = tryLoad(IMG_PATH_TRUCK);
    m_imgCoin       = tryLoad(IMG_PATH_COIN);
    m_imgRoad       = tryLoad(IMG_PATH_ROAD);
    m_imgRoadside   = tryLoad(IMG_PATH_ROADSIDE);
}

GameView::~GameView()
{
    stopTimer();
}

int GameView::laneHeightPx() const
{
    return h() / GameConstants::LANES_COUNT_ON_FIELD;
}

int GameView::laneYtoScreen(int laneIndex) const
{
    return y() + laneIndex * laneHeightPx();
}

int GameView::gameXtoScreen(double gameX) const
{
    return x() + static_cast<int>(gameX * w());
}

void GameView::timerCallback(void* data)
{
    GameView* view = static_cast<GameView*>(data);
    view->refresh();
    if (view->m_hasTimeout)
        Fl::repeat_timeout(view->m_timeout, timerCallback, view);
}

void GameView::startTimer()
{
    if (!m_hasTimeout)
    {
        m_hasTimeout = true;
        Fl::add_timeout(m_timeout, timerCallback, this);
    }
}

void GameView::stopTimer()
{
    m_hasTimeout = false;
    Fl::remove_timeout(timerCallback, this);
}

void GameView::refresh()
{
    redraw();
}

void GameView::show()
{
    Fl_Double_Window::show();
    take_focus();
    startTimer();
}

int GameView::handle(int event)
{
    if (event == FL_KEYDOWN)
    {
        int key = Fl::event_key();

        if (key == FL_Escape || key == 'q' || key == 'Q')
        {
            stopTimer();
            hide();
            if (m_exitCallback) m_exitCallback();
            return 1;
        }

        if (m_keyCallback)
        {
            m_keyCallback(key);
            return 1;
        }
    }
    if (event == FL_FOCUS || event == FL_UNFOCUS)
        return 1;

    return Fl_Double_Window::handle(event);
}

void GameView::draw()
{
    fl_push_clip(x(), y(), w(), h());

    drawBackground();
    drawLanes();
    drawCoins();
    drawVehicles();
    drawPlayer();
    drawHUD();

    if (!m_game.isInitialized())
        drawGameOver();

    fl_pop_clip();
}

void GameView::drawBackground() const
{
    fl_color(fl_rgb_color(50, 50, 50));
    fl_rectf(x(), y(), w(), h());
}

void GameView::drawLanes() const
{
    int laneH = laneHeightPx();

    for (int i = 0; i < GameConstants::LANES_COUNT_ON_FIELD; ++i)
    {
        Lane* lane = const_cast<GameView*>(this)->m_game.getField()[i];
        if (!lane) continue;

        int ly = laneYtoScreen(i);

        if (lane->getType() == Lane::LaneType::ROAD)
        {
            if (m_imgRoad)
                m_imgRoad->draw(x(), ly, w(), laneH);
            else
            {
                fl_color(fl_rgb_color(80, 80, 80));
                fl_rectf(x(), ly, w(), laneH);
                fl_color(FL_YELLOW);
                fl_line_style(FL_DASH, 2);
                fl_line(x(), ly + laneH / 2, x() + w(), ly + laneH / 2);
                fl_line_style(0);
            }
        }
        else
        {
            if (m_imgRoadside)
                m_imgRoadside->draw(x(), ly, w(), laneH);
            else
            {
                fl_color(fl_rgb_color(34, 120, 15));
                fl_rectf(x(), ly, w(), laneH);
            }
        }

        fl_color(fl_rgb_color(60, 60, 60));
        fl_line(x(), ly, x() + w(), ly);
    }
}

void GameView::drawCoins() const
{
    int laneH   = laneHeightPx();
    int coinSize = static_cast<int>(GameConstants::COIN_WIDTH * w());
    if (coinSize < 4) coinSize = 4;

    for (int i = 0; i < GameConstants::LANES_COUNT_ON_FIELD; ++i)
    {
        Lane* lane = const_cast<GameView*>(this)->m_game.getField()[i];
        if (!lane) continue;

        int ly = laneYtoScreen(i);

        for (const Coin& coin : lane->getCoins())
        {
            int cx = gameXtoScreen(coin.getX());
            int cy = ly + (laneH - coinSize) / 2;

            if (m_imgCoin)
                m_imgCoin->draw(cx, cy, coinSize, coinSize);
            else
            {
                fl_color(FL_YELLOW);
                fl_pie(cx, cy, coinSize, coinSize, 0, 360);
            }
        }
    }
}

void GameView::drawVehicles() const
{
    int laneH    = laneHeightPx();
    int vehicleH = static_cast<int>(laneH * 0.75);

    for (int i = 0; i < GameConstants::LANES_COUNT_ON_FIELD; ++i)
    {
        Lane* lane = const_cast<GameView*>(this)->m_game.getField()[i];
        if (!lane || lane->getType() != Lane::LaneType::ROAD) continue;

        LaneRoad* roadLane = static_cast<LaneRoad*>(lane);
        int ly = laneYtoScreen(i) + (laneH - vehicleH) / 2;

        for (const Vehicle& v : roadLane->getVehicles())
        {
            int vx = gameXtoScreen(v.getX());
            int vw = static_cast<int>(v.getLength() * w());
            if (vw < 4) vw = 4;

            Fl_PNG_Image* img = nullptr;
            if (v.getLength() > GameConstants::MINIMAL_VEHICLE_LENGTH * 2.5)
                img = m_imgTruck.get();
            else
                img = (roadLane->isLeftToRight() ? m_imgGreenCar.get() : m_imgOrangeCar.get());

            if (img)
                img->draw(vx, ly, vw, vehicleH);
            else
            {
                fl_color(roadLane->isLeftToRight() ? FL_BLUE : FL_RED);
                fl_rectf(vx, ly, vw, vehicleH);
            }
        }
    }
}

void GameView::drawPlayer() const
{
    const Player& player = m_game.getPlayer();
    int laneH   = laneHeightPx();
    int playerW = static_cast<int>(GameConstants::PLAYER_WIDTH * w());
    if (playerW < 4) playerW = 4;

    int px      = gameXtoScreen(player.getX());
    int laneIdx = m_game.getPlayerLaneIndex();
    int py      = laneYtoScreen(laneIdx) + (laneH - playerW) / 2;

    if (m_imgChicken)
        m_imgChicken->draw(px, py, playerW, playerW);
    else
    {
        fl_color(FL_YELLOW);
        fl_pie(px, py, playerW, playerW, 0, 360);
    }
}

void GameView::drawHUD() const
{
    fl_color(FL_WHITE);
    fl_font(FL_HELVETICA_BOLD, 22);
    std::string score = "Coins: " + std::to_string(m_game.getPlayer().getCoins());
    fl_draw(score.c_str(), x() + 10, y() + 30);

    fl_font(FL_HELVETICA, 14);
    fl_draw("ESC - back to menu", x() + 10, y() + h() - 10);
}

void GameView::drawGameOver() const
{
    fl_color(fl_rgb_color(0, 0, 0));
    fl_rectf(x() + w()/4, y() + h()/3, w()/2, h()/4);

    fl_color(FL_RED);
    fl_font(FL_HELVETICA_BOLD, 36);
    fl_draw("GAME OVER", x() + w()/4 + 20, y() + h()/2);

    fl_color(FL_WHITE);
    fl_font(FL_HELVETICA, 18);
    std::string score = "Score: " + std::to_string(m_game.getPlayer().getCoins());
    fl_draw(score.c_str(), x() + w()/4 + 60, y() + h()/2 + 30);
}
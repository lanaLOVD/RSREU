#include "GameView.h"

const std::string GameView::WINDOW_NAME { "Crossy Road" };
const std::string GameView::IMG_PATH_CHICKEN { "Resources/chicken.png" };
const std::string GameView::IMG_PATH_GREEN_CAR { "Resources/green_car.png" };
const std::string GameView::IMG_PATH_ORANGE_CAR { "Resources/orange_car.png" };
const std::string GameView::IMG_PATH_COIN { "Resources/coin.png" };
const std::string GameView::IMG_PATH_ROAD { "Resources/lane_road.png" };
const std::string GameView::IMG_PATH_ROADSIDE { "Resources/lane_roadside.png" };

const std::string GameView::TEXT_HUD_SCORE{"Coins: "};
const std::string GameView::TEXT_GAME_OVER{"GAME OVER"};
const std::string GameView::TEXT_HUD_ESCAPE{"ESC - back to menu"};

GameView::GameView(int width, int height)
    : Fl_Double_Window(width, height, WINDOW_NAME.c_str())
    , m_rGame(Game::getInstance())
    , m_timeout(1.0 / 60.0)
    , m_hasTimeout(false)
{
    m_imgChicken = loadImage(IMG_PATH_CHICKEN);
    m_imgGreenCar = loadImage(IMG_PATH_GREEN_CAR);
    m_imgOrangeCar = loadImage(IMG_PATH_ORANGE_CAR);
    m_imgCoin = loadImage(IMG_PATH_COIN);
    m_imgRoad = loadImage(IMG_PATH_ROAD);
    m_imgRoadside = loadImage(IMG_PATH_ROADSIDE);

    position(0, 0);

    if (m_imgChicken)
    {
        m_scaledImageChicken = scaleImage(*m_imgChicken, calculateGameObjectWidthPx(GameConstants::PLAYER_WIDTH), calculateGameObjectHeightPx());
    }

    if (m_imgCoin)
    {
        m_scaledImageCoin = scaleImage(*m_imgCoin, calculateGameObjectWidthPx(GameConstants::COIN_WIDTH), calculateGameObjectHeightPx());
    }

    if (m_imgGreenCar)
    {
        m_scaledImageGreenCar = scaleImage(*m_imgGreenCar, calculateGameObjectWidthPx(GameConstants::VEHICLE_LENGTH), calculateGameObjectHeightPx());
    }

    if (m_imgOrangeCar)
    {
        m_scaledImageOrangeCar = scaleImage(*m_imgOrangeCar, calculateGameObjectWidthPx(GameConstants::VEHICLE_LENGTH), calculateGameObjectHeightPx());
    }

    if (m_imgRoad)
    {
        m_scaledImageRoad = scaleImage(*m_imgRoad, width, calculateGameObjectHeightPx());
    }

    if (m_imgRoadside)
    {
        m_scaledImageRoadside = scaleImage(*m_imgRoadside, width, calculateGameObjectHeightPx());
    }
}

std::unique_ptr<Fl_PNG_Image> GameView::loadImage(const std::string& rPath)
{
    std::unique_ptr<Fl_PNG_Image> image{ std::make_unique<Fl_PNG_Image>(rPath.c_str()) };

    if (image)
    {
        if (image->fail())
        {
            return nullptr;
        }
    }
    else
    {
        return nullptr;
    }

    return image;
}

std::unique_ptr<Fl_PNG_Image> GameView::scaleImage(Fl_PNG_Image& rImage, int width, int height)
{
    return std::unique_ptr<Fl_PNG_Image>(static_cast<Fl_PNG_Image*>( rImage.copy(width, height)));
}

GameView::~GameView()
{
    stopTimer();
}

int GameView::calculateGameObjectHeightPx() const
{
    return h() / GameConstants::LANES_COUNT_ON_FIELD;
}

int GameView::calculateLaneYtoScreen(int laneIndex) const
{
    return (m_rGame.getField().getSize() - laneIndex - 1) * calculateGameObjectHeightPx();
}

int GameView::calculateGameObjectXtoScreen(double gameX) const
{
    return static_cast<int>(gameX * w());
}

int GameView::calculateGameObjectWidthPx(double width) const
{
    return static_cast<int>(w() * width);
}

void GameView::timerCallback(void* pData)
{
    GameView* pView{ static_cast<GameView*>(pData) };
    pView->refresh();
    if (pView->m_hasTimeout)
        Fl::repeat_timeout(pView->m_timeout, timerCallback, pView);
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
        int key{ Fl::event_key() };

        switch (key)
        {
        case FL_Escape:
            stopTimer();
            hide();
            if (m_exitCallback) m_exitCallback();
            break;

        case FL_Up:
        case KEY_W_BIG:
        case KEY_W_SMALL:
            if (m_keysMoveForwardCallback)
            {
                m_keysMoveForwardCallback();
            }
            return 1;

        case FL_Left:
        case KEY_A_BIG:
            if (m_keysMoveLeftCallback)
            {
                m_keysMoveLeftCallback();
            }
            return 1;

        case FL_Right:
        case KEY_D_BIG:
        case KEY_D_SMALL:
            if (m_keysMoveRightCallback)
            {
                m_keysMoveRightCallback();
            }
            return 1;

        default:
            break;
        }
    }
    if (event == FL_FOCUS || event == FL_UNFOCUS)
        return 1;

    return Fl_Double_Window::handle(event);
}

void GameView::draw()
{
    fl_push_clip(0, 0, w(), h());

    drawBackground();
    drawLanes();
    drawCoins();
    drawVehicles();
    drawPlayer();
    drawHUD();

    if (!m_rGame.isInitialized())
        drawGameOver();

    fl_pop_clip();
}

void GameView::drawBackground() const
{
    fl_color(fl_rgb_color(BACKGROUD_COLOR_RED, BACKGROUD_COLOR_GREEN, BACKGROUD_COLOR_BLUE));
    fl_rectf(0, 0, w(), h());
}

void GameView::drawLanes() const
{
    int laneHeight{ calculateGameObjectHeightPx() };

    for (int i{ 0 }; i < this->m_rGame.getField().getSize(); ++i)
    {
        const Lane *pLane{ this->m_rGame.getField()[i]};
        if (!pLane) continue;

        int laneY{ calculateLaneYtoScreen(i) };

        if (pLane->getType() == Lane::LaneType::ROAD)
        {
            if (m_scaledImageRoad)
                m_scaledImageRoad->draw(0, laneY);
            else
            {
                fl_color(fl_rgb_color(LANE_ROAD_NO_TEXTURE_BACKGROUND_RED, LANE_ROAD_NO_TEXTURE_BACKGROUND_GREEN, LANE_ROAD_NO_TEXTURE_BACKGROUND_BLUE));
                fl_rectf(0, laneY, w(), laneHeight);
                fl_color(FL_YELLOW);
                fl_line_style(FL_DASH, 2);
                fl_line(0, laneY + laneHeight / 2, x() + w(), laneY + laneHeight / 2);
                fl_line_style(0);
            }
        }
        else
        {
            if (m_scaledImageRoadside)
                m_scaledImageRoadside->draw(0, laneY);
            else
            {
                fl_color(fl_rgb_color(LANE_ROADSIDE_NO_TEXTURE_BACKGROUND_RED, LANE_ROADSIDE_NO_TEXTURE_BACKGROUND_GREEN, LANE_ROADSIDE_NO_TEXTURE_BACKGROUND_BLUE));
                fl_rectf(0, laneY, w(), laneHeight);
            }
        }

        fl_color(fl_rgb_color(LANE_BORDER_RED, LANE_BORDER_GREEN, LANE_BORDER_BLUE));
        fl_line(0, laneY, x() + w(), laneY);
    }
}

void GameView::drawCoins() const
{
    int laneHeight{ calculateGameObjectHeightPx() };
    int coinSize{ static_cast<int>(GameConstants::COIN_WIDTH * w()) };
    if (coinSize < MINIMAL_OBJECT_LENGTH)
        coinSize = MINIMAL_OBJECT_LENGTH;

    for (int i{ 0 }; i < GameConstants::LANES_COUNT_ON_FIELD; ++i)
    {
        const Lane *pLane{ this->m_rGame.getField()[i]};
        if (!pLane) continue;

        int laneY{ calculateLaneYtoScreen(i) };

        for (const Coin& coin : pLane->getCoins())
        {
            int coinX{ calculateGameObjectXtoScreen(coin.getX()) };

            if (m_scaledImageCoin)
                m_scaledImageCoin->draw(coinX, laneY, coinSize, coinSize);
            else
            {
                fl_color(FL_YELLOW);
                fl_pie(coinX, laneY, coinSize, coinSize, 0, CIRCLE_NO_TEXTURE_ARC_DEGREES);
            }
        }
    }
}

void GameView::drawVehicles() const
{
    int laneHeight{ calculateGameObjectHeightPx() };

    for (int i{ 0 }; i < m_rGame.getField().getSize(); ++i)
    {
        const Lane *pLane = this->m_rGame.getField()[i];
        if (!pLane || pLane->getType() != Lane::LaneType::ROAD) continue;

        const LaneRoad *pRoadLane{ static_cast<const LaneRoad*>(pLane) };
        int laneY{ calculateLaneYtoScreen(i) };

        for (const Vehicle& rVehicle : pRoadLane->getVehicles())
        {
            int vehicleX{ calculateGameObjectXtoScreen(rVehicle.getX()) };
            int vehicleWidth{ static_cast<int>(rVehicle.getLength() * w()) };
            if (vehicleWidth < MINIMAL_OBJECT_LENGTH)
                vehicleWidth = MINIMAL_OBJECT_LENGTH;

            Fl_PNG_Image *img{ (pRoadLane->isLeftToRight() ? m_imgGreenCar.get() : m_imgOrangeCar.get()) };
            
            if (img)
                img->draw(vehicleX, laneY, vehicleWidth, laneHeight);
            else
            {
                fl_color(pRoadLane->isLeftToRight() ? FL_BLUE : FL_RED);
                fl_rectf(vehicleX, laneY, vehicleWidth, laneHeight);
            }
        }
    }
}

void GameView::drawPlayer() const
{
    const Player& rPlayer{ m_rGame.getPlayer() };
    int playerWidth{ static_cast<int>(GameConstants::PLAYER_WIDTH * w()) };
    if (playerWidth < MINIMAL_OBJECT_LENGTH)
        playerWidth = MINIMAL_OBJECT_LENGTH;

    int playerX{ calculateGameObjectXtoScreen(rPlayer.getX()) };
    int playerY{ calculateLaneYtoScreen(0) };

    if (m_imgChicken)
        m_imgChicken->draw(playerX, playerY, playerWidth, playerWidth);
    else
    {
        fl_color(FL_YELLOW);
        fl_pie(playerX, playerY, playerWidth, playerWidth, 0, CIRCLE_NO_TEXTURE_ARC_DEGREES);
    }
}

void GameView::drawHUD() const
{
    fl_color(FL_WHITE);
    fl_font(FL_HELVETICA_BOLD, HUD_FONT_SIZE_SCORE);
    std::string score{ TEXT_HUD_SCORE + std::to_string(m_rGame.getPlayer().getCoins()) };
    fl_draw(score.c_str(), HUD_LABEL_SCORE_X_IDENT, HUD_LABEL_SCORE_Y_IDENT);

    fl_font(FL_HELVETICA, HUD_FONT_SIZE_ESCAPE);
    fl_draw(TEXT_HUD_ESCAPE.c_str(), HUD_LABEL_ESCAPE_X_IDENT, h() - HUD_LABEL_ESCAPE_Y_IDENT);
}

void GameView::drawGameOver() const
{
    fl_color(fl_rgb_color(0, 0, 0));
    fl_rectf(w()/4, y() + h()/3, w()/2, h()/4);

    fl_color(FL_RED);
    fl_font(FL_HELVETICA_BOLD, HUD_FONT_SIZE_GAME_OVER);
    fl_draw(TEXT_GAME_OVER.c_str(), w() / 4 + HUD_GAME_OVER_X_IDENT, y() + h() / 2);

    fl_color(FL_WHITE);
    fl_font(FL_HELVETICA, HUD_FONT_SIZE_SCORE);
    std::string score{ TEXT_HUD_SCORE + std::to_string(m_rGame.getPlayer().getCoins()) };
    fl_draw(score.c_str(), w()/4 + HUD_GAME_OVER_SCORE_X_IDENT, y() + h()/2 + HUD_GAME_OVER_SCORE_Y_IDENT);
}
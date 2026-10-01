#include "Game.h"
#include <iostream>

Game::Game()
    : m_initialized(false)
    , m_running(false)
    , m_alive(false)
    , m_playerLaneIndex(0)
    , m_score(0)
    , m_player(
        GameConstants::TILES_PER_ROADSIDE_LANE / 2.0 * GameConstants::PLAYER_WIDTH,
        GameConstants::PLAYER_WIDTH,
        GameConstants::PLAYER_SPEED)
    , m_probabilityDistribution(0.0, 1.0)
    , m_vehicleSpeedDistribution(GameConstants::MINIMAL_VEHICLE_SPEED, GameConstants::MAXIMAL_VEHICLE_SPEED)
    , m_vehicleLengthDistribution(GameConstants::MINIMAL_VEHICLE_LENGTH, GameConstants::MAXIMAL_VEHICLE_LENGTH)
{
}

Game& Game::getInstance()
{
    static Game instance;
    return instance;
}

LaneRoadside* Game::createRoadsideLane()
{
    return new LaneRoadside(1.0);
}

LaneRoad* Game::createRoadLane()
{
    double speed       = m_vehicleSpeedDistribution(m_randGen);
    double spawnChance = 0.3;
    bool   leftToRight = (m_probabilityDistribution(m_randGen) > 0.5);
    return new LaneRoad(1.0, speed, GameConstants::PLAYER_WIDTH * 2, spawnChance, leftToRight);
}

void Game::spawnCoinsOnLane(Lane* lane)
{
    for (int tile = 0; tile < GameConstants::TILES_PER_ROADSIDE_LANE; ++tile)
    {
        if (m_probabilityDistribution(m_randGen) < 0.2 && lane->canSpawnCoin(tile))
        {
            double coinX = tile * GameConstants::COIN_WIDTH;
            lane->addCoin(Coin(coinX, GameConstants::COIN_WIDTH));
        }
    }
}

void Game::buildField()
{
    m_field.addLane(createRoadsideLane());

    for (int i = 1; i < GameConstants::LANES_COUNT_ON_FIELD - 1; ++i)
    {
        if (i == 1 || i == GameConstants::LANES_COUNT_ON_FIELD - 2)
            m_field.addLane(createRoadsideLane());
        else
            m_field.addLane(createRoadLane());
    }

    m_field.addLane(createRoadsideLane());

    for (size_t i = 0; i < m_field.getSize(); ++i)
        spawnCoinsOnLane(m_field[i]);
}

void Game::scrollField()
{
    Lane* removed = m_field.removeFirstLane();
    delete removed;

    Lane* newLane = (m_probabilityDistribution(m_randGen) < 0.25)
        ? static_cast<Lane*>(createRoadsideLane())
        : static_cast<Lane*>(createRoadLane());

    spawnCoinsOnLane(newLane);
    m_field.addLane(newLane);
}

void Game::initGame()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    while (m_field.getSize() > 0)
    {
        Lane* l = m_field.removeFirstLane();
        delete l;
    }

    buildField();

    m_playerLaneIndex = static_cast<int>(m_field.getSize()) - 1;

    m_player = Player(
        GameConstants::TILES_PER_ROADSIDE_LANE / 2.0 * GameConstants::PLAYER_WIDTH,
        GameConstants::PLAYER_WIDTH,
        GameConstants::PLAYER_SPEED);

    m_score       = 0;
    m_alive       = true;
    m_initialized = true;
}

void Game::startGame()
{
    if (!m_initialized) initGame();
    m_running = true;
    m_gameThread = std::thread(&Game::processGameLogic, this);
}

void Game::stopGame()
{
    m_running = false;
    if (m_gameThread.joinable())
        m_gameThread.join();
    m_initialized = false;
}

void Game::spawnCar(LaneRoad* lane)
{
    double length = m_vehicleLengthDistribution(m_randGen);
    double speed  = m_vehicleSpeedDistribution(m_randGen);
    double startX = lane->isLeftToRight() ? -length : lane->getWidth();
    lane->addVehicle(Vehicle(startX, length, speed));
}

void Game::checkCollisions()
{
    Lane* currentLane = m_field[m_playerLaneIndex];
    if (!currentLane) return;

    if (currentLane->getType() == Lane::LaneType::ROAD)
    {
        LaneRoad* road = static_cast<LaneRoad*>(currentLane);
        if (road->checkAllVehiclesCollision(m_player))
        {
            std::cout << "Player hit by vehicle!\n";
            m_alive       = false;
            m_running     = false;
            m_initialized = false;
            return;
        }
    }

    currentLane->collectCoins(m_player);
}

void Game::processGameLogic()
{
    while (m_running)
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            for (size_t i = 0; i < m_field.getSize(); ++i)
            {
                if (m_field[i]->getType() == Lane::LaneType::ROAD)
                {
                    LaneRoad* lane = static_cast<LaneRoad*>(m_field[i]);
                    lane->updateVehicles();

                    if (lane->canSpawnVehicle())
                    {
                        if (m_probabilityDistribution(m_randGen) <= lane->getVehicleSpawnChance())
                            spawnCar(lane);
                    }
                }
            }

            checkCollisions();
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(GameConstants::GAME_THREAD_SLEEP_MS));
    }
}

void Game::movePlayerLeft()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_alive) return;
    double newX = m_player.getX() - GameConstants::PLAYER_WIDTH;
    if (newX >= 0)
        m_player.setX(newX);
}

void Game::movePlayerRight()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_alive) return;
    double newX = m_player.getX() + GameConstants::PLAYER_WIDTH;
    if (newX + GameConstants::PLAYER_WIDTH <= 1.0)
        m_player.setX(newX);
}

void Game::movePlayerForward()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_alive) return;

    if (m_playerLaneIndex > 0)
    {
        --m_playerLaneIndex;
        ++m_score;

        if (m_playerLaneIndex < GameConstants::LANES_COUNT_ON_FIELD / 2)
        {
            scrollField();
            m_playerLaneIndex = GameConstants::LANES_COUNT_ON_FIELD / 2;
        }
    }
}
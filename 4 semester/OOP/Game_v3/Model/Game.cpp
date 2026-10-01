#include "Game.h"

/**
 * Реализация конструктора по умолчанию
 */
Game::Game()
    : m_initialized(false)
    , m_running(false)
    , m_alive(false)
    , m_player(
        GameConstants::TILES_PER_ROADSIDE_LANE / 2.0 * GameConstants::PLAYER_WIDTH,
        GameConstants::PLAYER_WIDTH,
        GameConstants::PLAYER_SPEED)
    , m_probabilityDistribution(0.0, 1.0)
    , m_vehicleSpeedDistribution(GameConstants::MINIMAL_VEHICLE_SPEED, GameConstants::MAXIMAL_VEHICLE_SPEED)
{
}

/**
 * Реализация создания и получения ссылки на единственный объект класса
 */
Game& Game::getInstance()
{
    static Game instance;
    return instance;
}

/**
 * Реализация создания дорожки с обочиной
 */
std::shared_ptr<LaneRoadside> Game::createRoadsideLane() const
{
    return std::make_shared<LaneRoadside>(1.0);
}

/**
 * Реализация создания дорожки с проезжей частью
 */
std::shared_ptr<LaneRoad> Game::createRoadLane()
{
    double speed{ m_vehicleSpeedDistribution(m_randGen) };
    bool leftToRight{ (m_probabilityDistribution(m_randGen) <= GameConstants::CAR_LEFT_TO_RIGHT_CHANCE) };
    return std::make_shared<LaneRoad>(1.0, speed, GameConstants::PLAYER_WIDTH * 2, GameConstants::COIN_SPAWN_CHANCE, leftToRight);
}

/**
 * Реализация создания монет на дорожке
 * Lane *lane - сырой указатель на дорожку, где создаются монеты
 */
void Game::spawnCoinsOnLane(Lane *lane)
{
    for (int tile{ 0 }; tile < GameConstants::TILES_PER_ROADSIDE_LANE; ++tile)
    {
        if (m_probabilityDistribution(m_randGen) <= GameConstants::COIN_SPAWN_CHANCE && lane->canSpawnCoin(tile))
        {
            lane->addCoin(Coin(tile * GameConstants::COIN_WIDTH, GameConstants::COIN_WIDTH));
        }
    }
}

/**
 * Реализация создания поля при загрузке игры
 */
void Game::buildField()
{
    m_field.addLane(createRoadsideLane());

    for (int i{ 1 }; i < GameConstants::LANES_COUNT_ON_FIELD - 1; ++i)
    {
        std::shared_ptr<Lane> lane{ createRandomLane() };

        spawnCoinsOnLane(lane.get());

        m_field.addLane(lane);
    }
}

/**
 * Реализация создания случайной дорожки
 */
std::shared_ptr<Lane> Game::createRandomLane()
{
    if (m_probabilityDistribution(m_randGen) <= GameConstants::LANE_ROAD_SPAWN_CHANCE)
    {
        return createRoadLane();
    }
    else
    {
        return createRoadsideLane();
    }
}

/**
 * Реализация удаления первой дорожки и добавления новой дорожки в конец поля
 */
void Game::scrollField()
{
    m_field.removeFirstLane();

    std::shared_ptr<Lane> newLane{ createRandomLane() };

    spawnCoinsOnLane(newLane.get());
    m_field.addLane(newLane);
}

/**
 * Реализация инициализации игры
 */
void Game::initGame()
{
    std::lock_guard<std::mutex> lock(m_mutex);

    m_field.clear();

    buildField();

    m_player = Player(
        GameConstants::TILES_PER_ROADSIDE_LANE / 2.0 * GameConstants::PLAYER_WIDTH,
        GameConstants::PLAYER_WIDTH,
        GameConstants::PLAYER_SPEED);
    
    m_alive = true;
    m_initialized = true;
}

/**
 * Запуск игры
 */
void Game::startGame()
{
    if (!m_initialized) initGame();
    m_running = true;
    m_gameThread = std::thread(&Game::processGameLogic, this);
}

/**
 * Остановка игры
 */
void Game::stopGame()
{
    m_running = false;
    if (m_gameThread.joinable())
        m_gameThread.join();
    m_initialized = false;
}

/**
 * Реализация создания машины
 * LaneRoad *pLane - сырой указатель на дорожку, где создается машина
 */
void Game::spawnCar(LaneRoad *pLane)
{
    double length{ GameConstants::VEHICLE_LENGTH };
    double startX{ pLane->isLeftToRight() ? -length : pLane->getWidth() };
    pLane->addVehicle(Vehicle(startX, length, pLane->getVehiclesSpeed()));
}

/**
 * Реализация проверки столкновения игрового персонажа с машинами
 */
void Game::checkCollisions()
{
    Lane *pCurrentLane{ m_field[0] };
    if (!pCurrentLane) return;

    if (pCurrentLane->getType() == Lane::LaneType::ROAD)
    {
        LaneRoad *pRoad{ static_cast<LaneRoad*>(pCurrentLane)};
        if (pRoad->checkAllVehiclesCollision(m_player))
        {
            m_alive       = false;
            m_running     = false;
            m_initialized = false;
            return;
        }
    }

    pCurrentLane->collectCoins(m_player);
}

/**
 * Реализация игровой логики
 */
void Game::processGameLogic()
{
    while (m_running)
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);

            checkCollisions();

            for (size_t i{ 0 }; i < m_field.getSize(); ++i)
            {
                if (m_field[i]->getType() == Lane::LaneType::ROAD)
                {
                    LaneRoad *pLane{ static_cast<LaneRoad*>(m_field[i]) };
                    pLane->updateVehicles();

                    if (pLane->canSpawnVehicle())
                    {
                        if (m_probabilityDistribution(m_randGen) <= pLane->getVehicleSpawnChance())
                            spawnCar(pLane);
                    }
                }
            }
        }

        std::this_thread::sleep_for(
            std::chrono::milliseconds(GameConstants::GAME_THREAD_SLEEP_MS));
    }
}

/**
 * Реализация движения игрового персонажа влево
 */
void Game::movePlayerLeft()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_alive) return;
    double stepX{ -GameConstants::PLAYER_WIDTH };
    if (m_player.getX() >= GameConstants::PLAYER_WIDTH)
        m_player.move(stepX);
}

/**
 * Реализация движения игрового персонажа вправо
 */
void Game::movePlayerRight()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_alive) return;
    double stepX{ GameConstants::PLAYER_WIDTH };
    if (m_player.getX() + stepX <= 1.0 - GameConstants::PLAYER_WIDTH)
        m_player.move(stepX);
}

/**
 * Реализация движения игрового персонажа вперед
 */
void Game::movePlayerForward()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    if (!m_alive) return;

    scrollField();
}
#include "GameModel.h"
#include <mutex>

/**
 * @brief Конструктор: инициализирует RNG и вызывает reset() для начальной расстановки объектов.
 */
GameModel::GameModel()
    : m_cameraX{ 0 }, m_worldWidth{ 2000 }, m_isGameOver{ false }, m_isRunning{ false },
      m_rng{ std::random_device()() }, m_dist{ 0.0, 1.0 } {
    reset();
}

/**
 * @brief Деструктор: останавливает игровой поток и очищает объекты.
 */
GameModel::~GameModel() {
    stop();
    clearAllObjects();
}

/**
 * @brief Возвращает смещение камеры по X.
 * @return Значение m_cameraX
 */
double GameModel::getCameraX() const {
    return m_cameraX;
}

/**
 * @brief Возвращает указатель на игрока.
 * @return Указатель на объект Player
 */
Player* GameModel::getPlayer() {
    return m_player.get();
}

/**
 * @brief Возвращает флаг завершения игры.
 * @return true, если игра завершена
 */
bool GameModel::getGameOver() const {
    return m_isGameOver;
}

/**
 * @brief Возвращает флаг работающего игрового цикла.
 * @return true, если цикл активен
 */
bool GameModel::isGameRunning() const {
    return m_isRunning;
}

/**
 * @brief Запускает игровой цикл в отдельном потоке (60 тиков/сек).
 *
 * Если цикл уже запущен — сначала останавливает его.
 */
void GameModel::start() {
    if (m_isRunning) {
        stop();
    }

    m_isRunning = true;
    m_isGameOver = false;

    m_updateThread = std::thread([this]() {
        using clock = std::chrono::steady_clock;
        const auto updateInterval = std::chrono::microseconds(1000000 / 60);

        while (!m_isGameOver && m_isRunning) {
            auto start = clock::now();
            update();
            auto end = clock::now();

            auto elapsed = end - start;
            if (elapsed < updateInterval) {
                std::this_thread::sleep_for(updateInterval - elapsed);
            }
        }
    });
}

/**
 * @brief Останавливает игровой цикл и ожидает завершения потока.
 */
void GameModel::stop() {
    m_isGameOver = true;
    m_isRunning = false;
    if (m_updateThread.joinable()) {
        m_updateThread.join();
    }
}

/**
 * @brief Сбрасывает мир: очищает объекты, создаёт начальные платформы, врагов, монеты.
 *
 * Если цикл был запущен — останавливает его и перезапускает после сброса.
 */
void GameModel::reset() {
    bool wasRunning = m_isRunning;
    if (wasRunning) {
        stop();
    }

    {
        std::lock_guard<std::mutex> lock(m_dataMutex);
        m_platforms.clear();
        m_enemies.clear();
        m_coins.clear();

        m_platforms.shrink_to_fit();
        m_enemies.shrink_to_fit();
        m_coins.shrink_to_fit();

        if (m_player) {
            m_player.reset();
        }
        m_player = std::make_unique<Player>(100, 300);
        m_player->reset();

        m_cameraX = 0;
        m_worldWidth = 2000;
        m_isGameOver = false;

        // Начальная стартовая платформа
        m_platforms.push_back(std::make_unique<Platform>(0, 550, 800, 20));

        // Начальные враги на стартовой платформе
        m_enemies.push_back(std::make_unique<Enemy>(200, 510, 2, false));
        m_enemies.push_back(std::make_unique<Enemy>(400, 510, 2, true));
        m_enemies.push_back(std::make_unique<Enemy>(600, 510, 3, false));

        generateWorldSegment(800, m_worldWidth);
    }

    if (wasRunning) {
        start();
    }
}

/**
 * @brief Очищает все игровые объекты (вызывается под захваченным мьютексом).
 */
void GameModel::clearAllObjects() {
    std::lock_guard<std::mutex> lock(m_dataMutex);

    m_platforms.clear();
    m_enemies.clear();
    m_coins.clear();

    m_platforms.shrink_to_fit();
    m_enemies.shrink_to_fit();
    m_coins.shrink_to_fit();

    if (m_player) {
        m_player.reset();
    }
}

/**
 * @brief Обновляет состояние мира за один тик.
 *
 * Обновляет игрока, врагов, камеру, генерирует новые участки мира,
 * проверяет столкновения, удаляет неактивные объекты.
 */
void GameModel::update() {
    if (!m_isRunning || m_isGameOver) return;

    std::lock_guard<std::mutex> lock(m_dataMutex);

    if (!m_player) return;

    m_player->update();

    for (auto& enemy : m_enemies) {
        if (enemy) {
            enemy->update();
            enemy->applyGravity(m_platforms);
        }
    }

    // Сдвигаем камеру за игроком
    if (m_player->getX() > m_cameraX + 400) {
        m_cameraX = m_player->getX() - 400;
    }

    // Генерируем новый участок мира при приближении игрока к краю
    if (m_player->getX() > m_worldWidth - 1000) {
        m_worldWidth += 1000;
        generateMoreWorld();
    }

    checkCollisions();

    // Удаляем неактивных врагов
    m_enemies.erase(std::remove_if(m_enemies.begin(), m_enemies.end(),
        [](const auto& e) { return !e || !e->getActive(); }),
        m_enemies.end());

    // Удаляем собранные монеты
    m_coins.erase(std::remove_if(m_coins.begin(), m_coins.end(),
        [](const auto& c) { return !c || !c->getActive(); }),
        m_coins.end());

    // Проверяем гибель игрока
    if (!m_player->getActive()) {
        m_isGameOver = true;
        m_isRunning = false;
    }
}

/**
 * @brief Обрабатывает столкновения игрока с платформами, врагами и монетами.
 */
void GameModel::checkCollisions() {
    if (!m_player) return;

    // Столкновения с платформами (приземление сверху)
    for (auto& platform : m_platforms) {
        if (platform && platform->getActive() && m_player->collidesWith(*platform)) {
            if (m_player->getY() + m_player->getHeight() > platform->getY() &&
                m_player->getY() < platform->getY()) {
                m_player->setPosition(m_player->getX(), platform->getY() - m_player->getHeight());
                static_cast<Player*>(m_player.get())->stopJump();
            }
        }
    }

    // Столкновения с врагами
    for (auto& enemy : m_enemies) {
        if (enemy && enemy->getActive() && m_player->collidesWith(*enemy)) {
            Player* playerPtr = static_cast<Player*>(m_player.get());
            double playerBottom   = m_player->getY() + m_player->getHeight();
            double playerVelocityY = playerPtr->getVelocityY();

            double enemyTop   = enemy->getY();
            bool playerAboveEnemy = (playerBottom <= enemyTop + 15);
            bool playerFalling    = (playerVelocityY > 1);

            if (playerAboveEnemy && playerFalling) {
                // Игрок прыгнул на врага — убиваем врага
                enemy->setActive(false);
                playerPtr->addCoin();
            } else {
                // Боковое столкновение — наносим урон игроку
                if (!playerPtr->getIsInvulnerable()) {
                    playerPtr->takeDamage();

                    if (playerPtr->getLives() <= 0) {
                        m_isGameOver = true;
                        m_isRunning = false;
                    }
                }
            }
        }
    }

    // Сбор монет
    for (auto& coin : m_coins) {
        if (coin && coin->getActive() && m_player->collidesWith(*coin)) {
            m_player->addCoin();
            coin->setActive(false);
        }
    }
}

/**
 * @brief Генерирует очередной участок мира при продвижении игрока.
 */
void GameModel::generateMoreWorld() {
    generateWorldSegment(m_worldWidth - 500, m_worldWidth + 500);
}

/**
 * @brief Процедурно генерирует участок мира между startX и endX.
 *
 * Создаёт платформы, монеты на них и случайных врагов.
 *
 * @param startX  Начальная X-координата сегмента
 * @param endX    Конечная X-координата сегмента
 */
void GameModel::generateWorldSegment(double startX, double endX) {
    double currentX  = startX;
    double lastHeight = 550;

    // Нижняя «земля» для всего сегмента
    double bottomPlatformY = 599;
    m_platforms.push_back(std::make_unique<Platform>(
        currentX, bottomPlatformY, endX - startX + 500, 50));

    while (currentX < endX) {
        double segmentWidth  = 150 + m_dist(m_rng) * 2;
        double segmentHeight = lastHeight - 50 + m_dist(m_rng) * 120;
        segmentHeight = std::max(350.0, std::min(580.0, segmentHeight));

        if (segmentHeight < bottomPlatformY - 50) {
            double platformWidth = 120 + m_dist(m_rng) * 80;
            m_platforms.push_back(std::make_unique<Platform>(
                currentX, segmentHeight, platformWidth, 20));

            // Монеты над платформой
            if (m_dist(m_rng) > 0.1) {
                for (int i = 0; i < 2; i++) {
                    m_coins.push_back(std::make_unique<Coin>(
                        currentX + 20 + i * 40, segmentHeight - 50));
                }
            }

            // Случайный враг на платформе
            if (m_dist(m_rng) > 0.43) {
                double enemyX = currentX + 30;
                double enemyY = segmentHeight - 40;

                try {
                    auto enemy = std::make_unique<Enemy>(
                        enemyX, enemyY,
                        1.5 + m_dist(m_rng) * 1.5,
                        m_dist(m_rng) > 0.5);
                    if (enemy) {
                        m_enemies.push_back(std::move(enemy));
                    }
                } catch (const std::exception&) {
                    // Не удалось создать врага — пропускаем
                }
            }
        }

        currentX += segmentWidth;
        lastHeight = segmentHeight;
    }
}

/**
 * @brief Возвращает список платформ.
 * @return Ссылка на вектор платформ
 */
std::vector<std::unique_ptr<Platform>>& GameModel::getPlatforms() {
    return m_platforms;
}

/**
 * @brief Возвращает список врагов.
 * @return Ссылка на вектор врагов
 */
std::vector<std::unique_ptr<Enemy>>& GameModel::getEnemies() {
    return m_enemies;
}

/**
 * @brief Возвращает список монет.
 * @return Ссылка на вектор монет
 */
std::vector<std::unique_ptr<Coin>>& GameModel::getCoins() {
    return m_coins;
}

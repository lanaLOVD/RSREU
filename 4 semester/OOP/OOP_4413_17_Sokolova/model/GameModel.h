#pragma once

#include <vector>
#include <memory>
#include <random>
#include <thread>
#include <atomic>
#include <chrono>
#include <algorithm>
#include <mutex>
#include <functional>
#include "Player.h"
#include "Platform.h"
#include "Enemy.h"
#include "Coin.h"

/**
 * @brief Игровая модель — хранит всё состояние игрового мира.
 *
 * Управляет игроком, платформами, врагами и монетами.
 * Обновляет мир в отдельном потоке с частотой 60 тиков/сек.
 * Потокобезопасный доступ к данным обеспечивается через withDataLock().
 */
class GameModel {
private:
    /// @brief Игрок (владеющий указатель)
    std::unique_ptr<Player> m_player;

    /// @brief Список платформ в мире (владеющие указатели)
    std::vector<std::unique_ptr<Platform>> m_platforms;

    /// @brief Список активных врагов (владеющие указатели)
    std::vector<std::unique_ptr<Enemy>> m_enemies;

    /// @brief Список активных монет (владеющие указатели)
    std::vector<std::unique_ptr<Coin>> m_coins;

    /// @brief Смещение камеры по оси X (следует за игроком)
    double m_cameraX;

    /// @brief Текущая правая граница генерируемого мира
    double m_worldWidth;

    /// @brief Флаг завершения игры (атомарный для межпоточного доступа)
    std::atomic<bool> m_isGameOver{ false };

    /// @brief Флаг активного состояния игрового цикла
    std::atomic<bool> m_isRunning{ false };

    /// @brief Генератор псевдослучайных чисел Mersenne Twister
    std::mt19937 m_rng;

    /// @brief Равномерное распределение [0, 1) для процедурной генерации мира
    std::uniform_real_distribution<double> m_dist;

    /// @brief Поток игрового цикла обновления
    std::thread m_updateThread;

    /// @brief Мьютекс для защиты игровых данных при многопоточном доступе
    std::mutex m_dataMutex;

    /**
     * @brief Генерирует сегмент мира между двумя X-координатами.
     * @param startX  Начало сегмента
     * @param endX    Конец сегмента
     */
    void generateWorldSegment(double startX, double endX);

    /**
     * @brief Очищает все игровые объекты.
     *
     * Должна вызываться под захваченным мьютексом.
     */
    void clearAllObjects();

public:
    /**
     * @brief Конструктор: инициализирует RNG и создаёт начальный мир.
     */
    GameModel();

    /**
     * @brief Деструктор: останавливает поток и освобождает ресурсы.
     */
    ~GameModel();

    /**
     * @brief Возвращает указатель на игрока.
     * @return Сырой указатель на объект Player (не владеющий)
     */
    Player* getPlayer();

    /**
     * @brief Возвращает список платформ.
     * @return Ссылка на вектор владеющих указателей на платформы
     */
    std::vector<std::unique_ptr<Platform>>& getPlatforms();

    /**
     * @brief Возвращает список врагов.
     * @return Ссылка на вектор владеющих указателей на врагов
     */
    std::vector<std::unique_ptr<Enemy>>& getEnemies();

    /**
     * @brief Возвращает список монет.
     * @return Ссылка на вектор владеющих указателей на монеты
     */
    std::vector<std::unique_ptr<Coin>>& getCoins();

    /**
     * @brief Возвращает текущее смещение камеры по X.
     * @return Смещение камеры в пикселях
     */
    double getCameraX() const;

    /**
     * @brief Возвращает флаг завершения игры.
     * @return true, если игра завершена
     */
    bool getGameOver() const;

    /**
     * @brief Возвращает флаг работающего игрового цикла.
     * @return true, если цикл активен
     */
    bool isGameRunning() const;

    /**
     * @brief Выполняет функцию под защитой мьютекса данных.
     *
     * Используется View для безопасного чтения игровых объектов
     * без риска гонки данных с потоком обновления.
     *
     * @param func  Функция, которую нужно выполнить под блокировкой
     */
    void withDataLock(std::function<void()> func) {
        std::lock_guard<std::mutex> lock(m_dataMutex);
        func();
    }

    /**
     * @brief Запускает игровой цикл в отдельном потоке (60 тиков/сек).
     */
    void start();

    /**
     * @brief Останавливает игровой цикл и ожидает завершения потока.
     */
    void stop();

    /**
     * @brief Сбрасывает мир в начальное состояние.
     *
     * Очищает объекты, создаёт начальные платформы, врагов, монеты и игрока.
     */
    void reset();

    /**
     * @brief Обновляет состояние мира за один тик.
     *
     * Вызывается из потока обновления.
     */
    void update();

    /**
     * @brief Обрабатывает столкновения игрока с объектами мира.
     */
    void checkCollisions();

    /**
     * @brief Генерирует следующий участок мира при движении игрока вперёд.
     */
    void generateMoreWorld();

    /**
     * @brief Обрабатывает ввод пользователя — передаёт команды игроку.
     *
     * Вся логика управления игроком сосредоточена в модели,
     * контроллер только передаёт флаги нажатых клавиш.
     *
     * @param left     true, если нажата клавиша движения влево
     * @param right    true, если нажата клавиша движения вправо
     * @param jump     true, если нажата клавиша прыжка
     * @param running  true, если зажат Shift (бег)
     */
    void handleInput(bool left, bool right, bool jump, bool running);
};
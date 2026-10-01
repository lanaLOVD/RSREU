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
    /// @brief Игрок
    std::unique_ptr<Player> m_player;

    /// @brief Список платформ в мире
    std::vector<std::unique_ptr<Platform>> m_platforms;

    /// @brief Список активных врагов
    std::vector<std::unique_ptr<Enemy>> m_enemies;

    /// @brief Список активных монет
    std::vector<std::unique_ptr<Coin>> m_coins;

    /// @brief Смещение камеры по оси X
    double m_cameraX;

    /// @brief Текущая ширина генерируемого мира
    double m_worldWidth;

    /// @brief Флаг завершения игры (атомарный для межпоточного доступа)
    std::atomic<bool> m_isGameOver{ false };

    /// @brief Флаг активного состояния игрового цикла
    std::atomic<bool> m_isRunning{ false };

    /// @brief Генератор случайных чисел
    std::mt19937 m_rng;

    /// @brief Равномерное распределение [0, 1) для процедурной генерации
    std::uniform_real_distribution<double> m_dist;

    /// @brief Поток игрового цикла обновления
    std::thread m_updateThread;

    /// @brief Мьютекс для защиты игровых данных
    std::mutex m_dataMutex;

    /**
     * @brief Генерирует сегмент мира между двумя X-координатами.
     * @param startX  Начало сегмента
     * @param endX    Конец сегмента
     */
    void generateWorldSegment(double startX, double endX);

    /**
     * @brief Очищает все игровые объекты (под захваченным мьютексом).
     */
    void clearAllObjects();

public:
    /** @brief Конструктор: инициализирует мир и сбрасывает состояние */
    GameModel();

    /** @brief Деструктор: останавливает поток и освобождает ресурсы */
    ~GameModel();

    /** @brief Возвращает указатель на игрока */
    Player* getPlayer();

    /** @brief Возвращает список платформ */
    std::vector<std::unique_ptr<Platform>>& getPlatforms();

    /** @brief Возвращает список врагов */
    std::vector<std::unique_ptr<Enemy>>& getEnemies();

    /** @brief Возвращает список монет */
    std::vector<std::unique_ptr<Coin>>& getCoins();

    /** @brief Возвращает текущее смещение камеры */
    double getCameraX() const;

    /** @brief Возвращает true, если игра завершена */
    bool getGameOver() const;

    /** @brief Возвращает true, если игровой цикл запущен */
    bool isGameRunning() const;

    /**
     * @brief Выполняет функцию под защитой мьютекса данных.
     *
     * Используется View для безопасного чтения игровых объектов.
     * @param func  Функция, которую нужно выполнить под блокировкой
     */
    void withDataLock(std::function<void()> func) {
        std::lock_guard<std::mutex> lock(m_dataMutex);
        func();
    }

    /** @brief Запускает игровой цикл в отдельном потоке */
    void start();

    /** @brief Останавливает игровой цикл и ждёт завершения потока */
    void stop();

    /** @brief Сбрасывает мир в начальное состояние */
    void reset();

    /** @brief Обновляет состояние мира за один тик (вызывается из потока) */
    void update();

    /** @brief Обрабатывает столкновения игрока с объектами мира */
    void checkCollisions();

    /** @brief Генерирует следующий участок мира при движении игрока */
    void generateMoreWorld();
};

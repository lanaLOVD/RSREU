#ifndef GAME_MODEL_H
#define GAME_MODEL_H

#include "Field.h"
#include "Player.h"
#include "LaneRoad.h"
#include "LaneRoadside.h"
#include "GameConstants.h"

#include <chrono>
#include <thread>
#include <mutex>
#include <random>

/**
 * Класс, содержащий игровую логику
 */
class Game final
{
private:
	/**
	 * Конструктор по умолчанию закрыт для реализации шаблона проектирования Singleton
	 */
	Game();

	/**
	 * Игровое поле
	 */
	Field  m_field;

	/**
	 * Управляемый игроком персонаж
	 */
	Player m_player;

	/**
	 * Инициализатор для генератора псевдослучайных значений
	 */
	std::random_device m_randomDevice;

	/**
	 * Генератор псевдослучайных значений
	 */
	std::mt19937 m_randGen;

	/**
	 * Равномерное распределение для значений вероятности
	 */
	std::uniform_real_distribution<double> m_probabilityDistribution;

	/**
	 * Равномерное распределение для скорости машин
	 */
	std::uniform_real_distribution<double> m_vehicleSpeedDistribution;

	/**
	 * Флаг, обозначающий, что игра запущена
	*/
	std::atomic<bool> m_running;

	/**
	 * Флаг, обозначающий, что игра инициализирована
	 */
	bool m_initialized;

	/**
	 * Флаг, обозначающий, что управляемый персонаж жив
	*/
	bool m_alive;

	/**
	 * Средство синхронизации
	 */
	std::mutex  m_mutex;

	/**
	 * Объект потока, используемый для обработки игровой логики
	 */
	std::thread m_gameThread;

	/**
	 * Создание машины
	 * LaneRoad *pLane - сырой указатель на дорожку, где создается машина
	 */
	void spawnCar(LaneRoad *pLane);

	/**
	 * Создание поля при инициализации игры
	 */
	void buildField();

	/** 
	 * Удаление дорожки из начала поля и добавление новой дорожки в его конец
	*/
	void scrollField();

	/**
	 * Создание новой дорожки с проезжей частью
	 * Не const, поскольку задествован m_randGen
	 */
	std::shared_ptr<LaneRoad> createRoadLane();
	
	/**
	 * Создание дорожки с обочиной
	 */
	std::shared_ptr<LaneRoadside> createRoadsideLane() const;

	/**
	 * Создание случайной дорожки
	 * Не const, поскольку задествован m_randGen
	 */
	std::shared_ptr<Lane> createRandomLane();

	/**
	 * Создание монет на дорожке
	 * Lane *pLane - сырой указатель на дорожку, где создаются монеты
	 * Не const, поскольку задествован m_randGen
	 */
	void spawnCoinsOnLane(Lane *pLane);

	/**
	 * Проверка столкновения управляемого игроком персонажа с машиной
	 * В случае столкновения сбрасываются флаги m_running, m_alive и m_initialized
	 */
	void checkCollisions();

public:
	/**
	 * Удаление конструктора копии необходимо для реализации шаблона Singleton
	 */
	Game(const Game&) = delete;

	/**
	 * Получение ссылки на единственный объект класса
	 */
	static Game& getInstance();

	/**
	 * Подготовка игры
	 */
	void initGame();

	/**
	 * Запуск игры
	 */
	void startGame();

	/**
	 * Остановка игры
	 */
	void stopGame();

	/**
	 * Обработка игровой логики
	 */
	void processGameLogic();

	/**
	 * Движение игрового персонажа влево
	 */
	void movePlayerLeft();

	/**
	 * Движение игрового персонажа вправо
	 */
	void movePlayerRight();

	/**
	 * Движение игрового персонажа вперёд
	 */
	void movePlayerForward();

	/**
	 * Геттер для m_initialized
	 */
	bool isInitialized() const { return m_initialized; }

	/**
	 * Геттер для m_alive
	 */
	bool isAlive() const { return m_alive; }

	/**
	 * Геттер для m_running
	 */
	bool isRunning() const { return m_running; }

	/**
	 * Геттер для m_player
	 */
	const Player& getPlayer() const { return m_player; }

	/**
	 * Геттер для m_field
	 */
	Field& getField() { return m_field; }
};

#endif
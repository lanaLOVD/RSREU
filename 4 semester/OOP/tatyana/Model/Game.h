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
#include <atomic>

class Game final
{
private:
	Game();

	Field  m_field;
	Player m_player;

	int m_playerLaneIndex;
	int m_score;

	std::random_device m_randomDevice;
	std::mt19937 m_randGen;
	std::uniform_real_distribution<double> m_probabilityDistribution;
	std::uniform_real_distribution<double> m_vehicleSpeedDistribution;
	std::uniform_real_distribution<double> m_vehicleLengthDistribution;

	std::atomic<bool> m_running;
	bool m_initialized;
	bool m_alive;



	std::mutex  m_mutex;
	std::thread m_gameThread;

	void spawnCar(LaneRoad* lane);
	void buildField();
	void scrollField();
	LaneRoad*     createRoadLane();      // не const — использует m_randGen
	LaneRoadside* createRoadsideLane();

	void spawnCoinsOnLane(Lane* lane);
	void checkCollisions();

public:
	static Game& getInstance();

	void initGame();
	void startGame();
	void stopGame();
	void processGameLogic();

	void movePlayerLeft();
	void movePlayerRight();
	void movePlayerForward();

	bool isInitialized() const { return m_initialized; }
	bool isAlive()       const { return m_alive;        }
	bool isRunning()     const { return m_running;      }

	const Player& getPlayer()          const { return m_player;          }
	Field&        getField()                 { return m_field;            }  // не const — для отрисовки
	int           getPlayerLaneIndex() const { return m_playerLaneIndex; }
	int           getScore()           const { return m_score;           }
};

#endif
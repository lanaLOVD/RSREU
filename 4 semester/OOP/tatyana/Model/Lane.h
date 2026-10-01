#ifndef LANE_H
#define LANE_H

#include <list>

#include "GameConstants.h"
#include "Coin.h"
#include "Player.h"

class Lane
{
public:
	enum class LaneType
	{
		ROAD,
		ROADSIDE
	};

private:
	double           m_width;
	std::list<Coin>  m_coins;
	LaneType         m_type;

protected:
	Lane(double width, LaneType type) : m_width(width), m_type(type) {}

public:
	virtual ~Lane() {}

	double getWidth() const { return m_width; }

	void addCoin(const Coin& coin) { m_coins.push_back(coin); }

	LaneType getType() const { return m_type; }

	const std::list<Coin>& getCoins() const { return m_coins; }

	bool canSpawnCoin(int sectorIndex);

	// Проверяет пересечение игрока с монетами и собирает их
	void collectCoins(Player& player)
	{
		for (auto iter = m_coins.begin(); iter != m_coins.end(); )
		{
			if (iter->checkCollision(player))
			{
				player.addCoin();
				iter = m_coins.erase(iter);
			}
			else
			{
				++iter;
			}
		}
	}
};

#endif
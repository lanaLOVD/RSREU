#include "Lane.h"

/**
* Реализация проверки возможности создания монеты в заданной части дорожки
* int sectorIndex - индекс части дорожки, где предполагается создание монеты
* Ширина частей дорожки равна ширине монеты
*/
bool Lane::canSpawnCoin(int sectorIndex)
{
	double coinLeft{ sectorIndex * GameConstants::COIN_WIDTH };

	for (auto iter{ m_coins.begin() }; iter != m_coins.end(); ++iter)
	{
		if (iter->getX() == coinLeft)
		{
			return false;
		}
	}

	return true;
}

/**
* Реализация сбора монет, до которых дотронулся игрок
* Player& player - ссылка на объект, описывающий игрока
*/
void Lane::collectCoins(Player& player)
{
	for (auto iter{ m_coins.begin() }; iter != m_coins.end(); )
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
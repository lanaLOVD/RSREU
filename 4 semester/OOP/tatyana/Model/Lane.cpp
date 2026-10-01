#include "Lane.h"

bool Lane::canSpawnCoin(int sectorIndex)
{
	double coinLeft = sectorIndex * GameConstants::COIN_WIDTH;

	for (auto iter = m_coins.begin(); iter != m_coins.end(); ++iter)
	{
		if (iter->getX() == coinLeft)
		{
			return false;
		}
	}

	return true;
}

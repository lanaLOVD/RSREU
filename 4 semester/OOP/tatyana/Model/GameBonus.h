#ifndef GAME_BONUS_H
#define GAME_BONUS_H

#include "GameObject.h"

#include "GameBonusType.h"

class GameBonus : public GameObject 
{
public:
	GameBonusType getType()
	{
		return m_type;
	}

	virtual void take()
	{
	}

protected:
	GameBonus(double x, double length, GameBonusType type) : GameObject(x, length, 0), m_type(type)
	{
	}
private:
	GameBonusType m_type;
};

#endif
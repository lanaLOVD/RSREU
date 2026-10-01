#ifndef GAME_BONUS_H
#define GAME_BONUS_H

#include "GameObject.h"

#include "GameBonusType.h"

/**
 * Базовый класс для бонусов
 */
class GameBonus : public GameObject 
{
public:
	/**
	* Геттер для поля m_type
	*/
	GameBonusType getType()
	{
		return m_type;
	}

	/**
	 * Чистый виртуальный метод взятия бонусного объекта
	 */

	virtual void take() = 0;
	
protected:
	/**
	 * Конструктор
	 * double x - относительная координата левой стороны объекта
	 * double length - относительная длина объекта
	 */
	GameBonus(double x, double length, GameBonusType type) : GameObject(x, length, 0), m_type(type)
	{
	}
private:
	/**
 	* Тип бонусного объекта 
 	*/
	GameBonusType m_type;
};

#endif
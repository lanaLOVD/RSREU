#ifndef LANE_H
#define LANE_H

#include <list>

#include "GameConstants.h"
#include "Coin.h"
#include "Player.h"

/**
 * Базовый класс, описывающий дорожку игрового поля
 */
class Lane
{
public:
	/**
	 * Тип дорожки
	 */
	enum class LaneType
	{
		/**
		 * Проезжая часть
		 */
		ROAD,

		/**
		 * Обочина
		 */
		ROADSIDE
	};

private:
	/**
	 * Относительная ширина
	 */
	double m_width;

	/**
	 * Список лежащих на дорожке монет
	 */
	std::list<Coin> m_coins;

	/**
	 * Тип дорожки
	 */
	LaneType m_type;

protected:
	/**
	 * Конструктор
	 * double width - относительная ширина
	 * LaneType type - тип дорожки
	 */
	Lane(double width, LaneType type) : m_width(width), m_type(type) {}

public:
	/**
	 * Виртуальный деструктор
	 */
	virtual ~Lane() {}

	/**
	 * Геттер для поля m_width
	 */
	double getWidth() const { return m_width; }

	/**
	 * Добавление новой монеты
	 * const Coin& coin - ссылка на добавляемую монету
	 */
	void addCoin(const Coin& rCoin) { m_coins.push_back(rCoin); }

	/**
	 * Геттер для поля m_type
	 */
	LaneType getType() const { return m_type; }

	/**
	 * Геттер для поля m_coins
	 */
	const std::list<Coin>& getCoins() const { return m_coins; }

	/**
	 * Проверка возможности создания монеты в заданной части дорожки
	 * int sectorIndex - индекс части дорожки, где предполагается создание монеты
	 * Ширина частей дорожки равна ширине монеты
	 */
	bool canSpawnCoin(int sectorIndex);

	/**
	 * Сбор монет, до которых дотронулся игрок
	 * Player& player - ссылка на объект, описывающий игрока
	 */
	void collectCoins(Player& player);
};

#endif
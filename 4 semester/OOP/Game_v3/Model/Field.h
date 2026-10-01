#ifndef FIELD_H
#define FIELD_H

#include <deque>
#include <memory>
#include "Lane.h"

/**
 * Игровое поле
 */
class Field
{
private:
	/**
	 * Активные дорожки
	 */
	std::deque<std::shared_ptr<Lane>> m_lanes;

public:
	/**
	 * Конструтор по умолчанию
	*/
	Field() = default;

	/**
	 * Конструктор копирования удалён
	 */
	Field(const Field&) = delete;

	/**
	 * Удаление всех активных дорожек
	 */
	void clear();

	/**
	 * Добавление новой дорожки
	 * std::shared_ptr<Lane> lane - разделяемый указатель на новую дорожку
	 */
	void addLane(std::shared_ptr<Lane> lane)
	{
		m_lanes.push_back(lane);
	}

	/**
	 * Удаление первой дорожки
	 */
	void removeFirstLane();

	/**
	 * Возвращает количество активных дорожек
	 */
	size_t getSize() const
	{
		return m_lanes.size();
	}

	/**
	 * Оператор доступа по индексу
	 * Возвращает сырой указатель на дорожку, если индекс меньше количества активных дорожек, иначе nullptr
	 */
	Lane* operator[](size_t index)
	{
		if (index >= m_lanes.size()) return nullptr;
		return m_lanes[index].get();
	}
};

#endif
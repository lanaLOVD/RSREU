#include "LaneRoad.h"

/**
* Реализация обновления списка машин
*/
void LaneRoad::updateVehicles()
{
	double sign{ this->m_leftToRight ? 1.0 : -1.0 };

	std::list<Vehicle*> vehiclesToRemove;

	for (auto iter{ this->m_vehicles.begin() }; iter != m_vehicles.end(); ++iter)
	{
		iter->move(sign * iter->getSpeed());

		if (isCarOutOfLane(*iter))
		{
			vehiclesToRemove.push_back(&(*iter));
		}
	}

	for (Vehicle *pVehicle : vehiclesToRemove)
	{
		m_vehicles.remove(*pVehicle);
	}
}

/**
* Реализация проверки выхода машины за пределы дорожки
* const Vehicle& rVehicle - ссылка на машину
* Возвращает true, если машина полностью вышла за пределы дорожки, инача - false 
*/
bool LaneRoad::isCarOutOfLane(const Vehicle& rVehicle) const
{
	return (m_leftToRight && rVehicle.getX() > this->getWidth()) ||
		   (!m_leftToRight && rVehicle.getX() + rVehicle.getLength() < 0);
}

/**
* Реализация проверки возможности создания машины на дорожке
*/
bool LaneRoad::canSpawnVehicle() const
{
	for (const Vehicle& rVehicle : m_vehicles)
	{
		if ((m_leftToRight && rVehicle.getX() < m_minimalCarDistance) ||
			(!m_leftToRight && this->getWidth() - (rVehicle.getX() + rVehicle.getLength()) < m_minimalCarDistance))
		{
			return false;
		}
	}
	return true;
}

/**
* Реализация проверки заданного объекта на столкновение с каждой машиной на дорожке
* const GameObject& rObj - ссылка на проверяемый объект
* Возвращает true, если произошло столкновение с какой-либо из машин, иначе - false
*/
bool LaneRoad::checkAllVehiclesCollision(const GameObject& obj) const
{
	for (const Vehicle& rVehicle : m_vehicles)
	{
		if (rVehicle.checkCollision(obj))
			return true;
	}
	return false;
}
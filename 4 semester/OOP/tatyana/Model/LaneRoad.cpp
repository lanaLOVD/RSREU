#include "LaneRoad.h"

void LaneRoad::updateVehicles()
{
	double sign = this->m_leftToRight ? 1.0 : -1.0;

	std::list<Vehicle*> vehiclesToRemove;

	for (auto iter = this->m_vehicles.begin(); iter != m_vehicles.end(); ++iter)
	{
		iter->move(sign * iter->getSpeed());

		if (isCarOutOfLane(*iter))
		{
			vehiclesToRemove.push_back(&(*iter));
		}
	}

	for (auto* v : vehiclesToRemove)
	{
		m_vehicles.remove(*v);
	}
}

bool LaneRoad::isCarOutOfLane(const Vehicle& vehicle) const
{
	return (m_leftToRight && vehicle.getX() > this->getWidth()) ||
		   (!m_leftToRight && vehicle.getX() + vehicle.getLength() < 0);
}

bool LaneRoad::canSpawnVehicle() const
{
	for (const Vehicle& vehicle : m_vehicles)
	{
		if ((m_leftToRight && vehicle.getX() < m_minimalCarDistance) ||
			(!m_leftToRight && this->getWidth() - (vehicle.getX() + vehicle.getLength()) < m_minimalCarDistance))
		{
			return false;
		}
	}
	return true;
}

bool LaneRoad::checkAllVehiclesCollision(const GameObject& obj) const
{
	for (const Vehicle& vehicle : m_vehicles)
	{
		if (vehicle.checkCollision(obj))
			return true;
	}
	return false;
}
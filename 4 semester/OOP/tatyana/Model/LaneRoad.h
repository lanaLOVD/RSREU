#ifndef LANE_ROAD_H
#define LANE_ROAD_H

#include "Lane.h"
#include "Vehicle.h"

class LaneRoad : public Lane
{
private:
	std::list<Vehicle> m_vehicles;

	bool   m_leftToRight;
	double m_vehiclesSpeed;
	double m_minimalCarDistance;
	double m_vehicleSpawnChance;

	bool isCarOutOfLane(const Vehicle& vehicle) const;

public:
	LaneRoad(double width, double vehiclesSpeed, double minimalCarDistance,
			 double vehicleSpawnChance, bool left = true)
		: Lane(width, LaneType::ROAD)
		, m_vehiclesSpeed(vehiclesSpeed)
		, m_minimalCarDistance(minimalCarDistance)
		, m_vehicleSpawnChance(vehicleSpawnChance)
		, m_leftToRight(left)
	{}

	double getVehiclesSpeed()   const { return m_vehiclesSpeed;   }
	double getVehicleSpawnChance() const { return m_vehicleSpawnChance; }
	bool   isLeftToRight()      const { return m_leftToRight;     }

	const std::list<Vehicle>& getVehicles() const { return m_vehicles; }

	void addVehicle(const Vehicle& vehicle) { m_vehicles.push_back(vehicle); }
	void removeVehicle()                    { m_vehicles.pop_front(); }

	void updateVehicles();
	bool canSpawnVehicle() const;
	bool checkAllVehiclesCollision(const GameObject& obj) const;
};

#endif
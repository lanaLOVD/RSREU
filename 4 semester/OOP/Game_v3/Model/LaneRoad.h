#ifndef LANE_ROAD_H
#define LANE_ROAD_H

#include "Lane.h"
#include "Vehicle.h"

/**
 * Дорожка-проезжая часть
 */
class LaneRoad : public Lane
{
private:
	/**
	 * Список машин, проезжающих по дорожке
	*/
	std::list<Vehicle> m_vehicles;

	/**
	 * Направление движения машин
	 * true - слева направо
	 * false - справа налево
	 */
	bool m_leftToRight;

	/**
	 * Скорость машин, проезжающих по дорожке
	 */
	double m_vehiclesSpeed;

	/**
	 * Минимально необходимая дистанция между машинами
	 */
	double m_minimalCarDistance;

	/**
	 * Шанс появления машины на дорожке
	 */
	double m_vehicleSpawnChance;

	/**
	 * Проверка выхода машины за пределы дорожки
	 * const Vehicle& rVehicle - ссылка на машину
	 * Возвращает true, если машина полностью вышла за пределы дорожки, инача - false 
	 */
	bool isCarOutOfLane(const Vehicle& rVehicle) const;

public:
	/**
	 * Конструктор
	 * double width - относительная ширина дорожки
	 * double vehiclesSpeed - скорость появляющихся на дорожке машин
	 * double minimalCarDistance - минимально необходимая дистанция между машинами
	 * bool left - направление движения машин (true - слева направо, false - справа налево)
	 */
	LaneRoad(double width, double vehiclesSpeed, double minimalCarDistance,
			 double vehicleSpawnChance, bool left = true)
		: Lane(width, LaneType::ROAD)
		, m_vehiclesSpeed(vehiclesSpeed)
		, m_minimalCarDistance(minimalCarDistance)
		, m_vehicleSpawnChance(vehicleSpawnChance)
		, m_leftToRight(left)
	{}

	/**
	 * Геттер для поля m_vehiclesSpeed
	 */
	double getVehiclesSpeed() const { return m_vehiclesSpeed; }

	/**
	 * Геттер для поля m_vehicleSpawnChance
	 */
	double getVehicleSpawnChance() const { return m_vehicleSpawnChance; }

	/**
	 * Геттер для поля m_leftToRight
	 */
	bool   isLeftToRight() const { return m_leftToRight; }

	/**
	 * Геттер для поля m_vehicles
	 */
	const std::list<Vehicle>& getVehicles() const { return m_vehicles; }

	/**
	 * Добавление новой машины на дорожку
	 * const Vehicle& rVehicle - ссылка на добавляемую машину
	 */
	void addVehicle(const Vehicle& rVehicle) { m_vehicles.push_back(rVehicle); }

	/**
	 * Проверка каждой машины на выход за пределы дорожки
	 * и удаление машин, вышедших за пределы
	 */
	void updateVehicles();

	/**
	 * Проверка возможности создания машины на дорожке
	 */
	bool canSpawnVehicle() const;

	/**
	 * Проверка заданного объекта на столкновение с каждой машиной на дорожке
	 * const GameObject& rObj - ссылка на проверяемый объект
	 * Возвращает true, если произошло столкновение с какой-либо из машин, иначе - false
	 */
	bool checkAllVehiclesCollision(const GameObject& rObj) const;
};

#endif
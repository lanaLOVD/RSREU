//#ifndef ROAD_H
//#define ROAD_H
//
//#include <vector>
//#include <memory>
//#include "GameConstants.h"
//#include "Vehicle.h"
//
//class Road
//{
//private:
//    int m_laneCount;
//    double m_startY;
//    double m_laneHeight;
//    std::vector<std::vector<std::unique_ptr<Vehicle>>> m_lanes;
//
//public:
//    Road();
//    ~Road() = default;
//
//    void init();
//    void update(double elapsedTime);
//    void addVehicleToLane(int laneIndex, std::unique_ptr<Vehicle> vehicle);
//    void clearLane(int laneIndex);
//    const std::vector<std::unique_ptr<Vehicle>>& getVehiclesInLane(int laneIndex) const;
//    int getLaneCount() const { return m_laneCount; }
//    double getLaneY(int laneIndex) const;
//    bool isInRoad(double y) const;
//    int getLaneIndexByY(double y) const;
//};
//
//#endif
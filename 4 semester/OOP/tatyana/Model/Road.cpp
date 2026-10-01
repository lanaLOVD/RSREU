//#include "Road.h"
//
//Road::Road()
//    : m_laneCount(GameConstants::c_roadLanes)
//    , m_startY(GameConstants::c_fieldHeight / 3.0)
//    , m_laneHeight(GameConstants::c_fieldHeight * 0.6 / GameConstants::c_roadLanes)
//{
//    m_lanes.resize(m_laneCount);
//}
//
//void Road::init() {
//    for (auto& lane : m_lanes)
//    {
//        lane.clear();
//    }
//}
//
//void Road::update(double elapsedTime)
//{
//    for (auto& lane : m_lanes)
//    {
//        for (auto& vehicle : lane)
//        {
//            vehicle->update(elapsedTime);
//        }
//    }
//}
//
//void Road::addVehicleToLane(int laneIndex, std::unique_ptr<Vehicle> vehicle)
//{
//    if (laneIndex >= 0 && laneIndex < m_laneCount)
//    {
//        m_lanes[laneIndex].push_back(std::move(vehicle));
//    }
//}
//
//void Road::clearLane(int laneIndex)
//{
//    if (laneIndex >= 0 && laneIndex < m_laneCount)
//    {
//        m_lanes[laneIndex].clear();
//    }
//}
//
//const std::vector<std::unique_ptr<Vehicle>>& Road::getVehiclesInLane(int laneIndex) const
//{
//    static std::vector<std::unique_ptr<Vehicle>> empty;
//    if (laneIndex >= 0 && laneIndex < m_laneCount)
//    {
//        return m_lanes[laneIndex];
//    }
//    return empty;
//}
//
//double Road::getLaneY(int laneIndex) const
//{
//    return m_startY + laneIndex * m_laneHeight + m_laneHeight / 2.0;
//}
//
//bool Road::isInRoad(double y) const
//{
//    return y >= m_startY && y <= m_startY + m_laneCount * m_laneHeight;
//}
//
//int Road::getLaneIndexByY(double y) const
//{
//    if (!isInRoad(y))
//        return -1;
//
//    return static_cast<int>((y - m_startY) / m_laneHeight);
//}
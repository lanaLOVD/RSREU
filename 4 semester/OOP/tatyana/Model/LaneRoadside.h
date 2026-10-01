#ifndef LANE_ROADSIDE_H
#define LANE_ROADSIDE_H

#include "Lane.h"
#include "Barrier.h"

class LaneRoadside : public Lane
{
private:
	std::list<Barrier> m_barriers;


public:
	LaneRoadside(double width) : Lane(width, LaneType::ROADSIDE)
	{
	}

	void addBarrier(const Barrier& barrier)
	{
		m_barriers.push_back(barrier);
	}
};

#endif
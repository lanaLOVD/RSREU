#ifndef LANE_ROADSIDE_H
#define LANE_ROADSIDE_H

#include "Lane.h"

/**
 * Дорожка-обочина
 */
class LaneRoadside : public Lane
{
public:

	/**
	 * Конструктор
	 * double width - относительная ширина
	 */
	LaneRoadside(double width) : Lane(width, LaneType::ROADSIDE)
	{
	}
};

#endif
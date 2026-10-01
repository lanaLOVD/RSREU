#include "Field.h"

Field::~Field()
{
	for (auto iter = m_lanes.begin(); iter != m_lanes.end(); ++iter)
		delete *iter;
}

Lane* Field::removeFirstLane()
{
	Lane* firstLane = m_lanes.front();
	m_lanes.pop_front();
	return firstLane;
}
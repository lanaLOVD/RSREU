#ifndef FIELD_H
#define FIELD_H

#include <deque>
#include "Lane.h"

class Field
{
private:
	std::deque<Lane*> m_lanes;

public:
	~Field();

	void addLane(Lane* lane)
	{
		m_lanes.push_back(lane);
	}

	Lane* removeFirstLane();

	size_t getSize() const
	{
		return m_lanes.size();
	}

	// const и не-const версии оператора []
	Lane* operator[](size_t index)
	{
		if (index >= m_lanes.size()) return nullptr;
		return m_lanes[index];
	}

	const Lane* operator[](size_t index) const
	{
		if (index >= m_lanes.size()) return nullptr;
		return m_lanes[index];
	}
};

#endif
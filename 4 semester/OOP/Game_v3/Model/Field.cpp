#include "Field.h"

/**
 * Реализация удаления всех активных дорожек
 */
void Field::clear()
{
	this->m_lanes.clear();
}

/**
 * Реализация удаления первой дорожки
 */
void Field::removeFirstLane()
{
	m_lanes.pop_front();
}
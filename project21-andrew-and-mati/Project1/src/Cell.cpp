#include "Cell.h"

Cell::Cell()
{
	cellBody.setFillColor(sf::Color::Transparent);
	cellBody.setSize(sf::Vector2f(50, 50));
	cellBody.setOutlineThickness(1);
	cellBody.setOutlineColor(sf::Color::Green);
	m_id = -1;
	m_isPassable = true;
	m_previousCellId = -1;
}

void Cell::setMarked(bool t_mark)
{
	m_isMarked = t_mark;
}

void Cell::setParentCellId(int t_cellId)
{
	m_parentCellId = t_cellId;
}

bool Cell::isMarked() const
{
	return m_isMarked;
}

int Cell::getID() const
{
	return m_id;
}

void Cell::addNeighboursID(int t_id)
{
	neighboursids.push_back(t_id);
}

//void Cell::markImpassable(std::vector<Wall*>& t_globalWalls)
//{
//	for (Wall *w : t_globalWalls)
//	{
//		if (cellBody.getGlobalBounds().intersects(w->body.getGlobalBounds()))
//		{
//			if (!w->isOuter)
//			{
//				for (int i = 0; i < 26; i++)
//				{
//					m_isPassable = false;
//					cellBody.setFillColor(sf::Color(255, 0, 0, 130));
//
//				}
//				
//			}
//		}
//
//	}
//
//}
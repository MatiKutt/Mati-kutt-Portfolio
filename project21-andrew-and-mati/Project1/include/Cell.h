#pragma once
#include <iostream>
//#include "Wall.h"
#include <vector>
#include <queue>
#include <SFML/Graphics.hpp>

class Cell
{
public:
	Cell();

	sf::RectangleShape cellBody;
	int m_id{ - 1};
	int x;
	int y;
	int g_cost;
	int h_cost;
	int weight = 1;

	int m_previousCellId{ -1 };
	bool m_isPassable = true;
	sf::Text idText;
	std::vector<int> neighboursids;
	//void markImpassable(std::vector<Wall*>& t_globalWalls); this is legacy from previous project but might be needed later on
	std::string neighboursText;
	sf::Vector2f center;

	///breadthFirst
	bool m_isMarked{ false };
	int m_parentCellId;

	void setMarked(bool t_mark);
	void setParentCellId(int t_cellId);
	void addNeighboursID(int t_id);
	bool isMarked() const;
	int getID() const;
};

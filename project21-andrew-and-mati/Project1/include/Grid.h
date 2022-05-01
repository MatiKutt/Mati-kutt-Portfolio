#pragma once
#ifndef GRID
#define GRID


#include <SFML/Graphics.hpp>
#include <iostream>
//#include "Wall.h"
#include <vector>
#include <queue>
#include "Cell.h"
#include "GLOBALS.h"

class Grid
{
public:
	static const int xAmountCells = 20;
	static const int YAmountCells = 20;
	static const int TotalCells = 400;

	Cell* at(int t_index);
	Grid();
	//void setupGrid(std::vector<Wall*>& t_globalWalls);
	void setupGrid();
	void showNeighbours();
	sf::Font idFont;
	Cell cellGrid[xAmountCells][YAmountCells];
	void draw(sf::RenderWindow& m_window);
	void reset();
	bool traversible = true;
	int getCellPlayerIsIn(sf::Vector2f t_playerPos);
	void findNeigbours(int t_pointX, int t_pointY);
	void update();
	void aStar(Cell* t_start, Cell* t_dest, std::vector<int>* m_path);
	void showAStar();
	Cell* GetIntersects(sf::Vector2f pos);
};

#endif // !GRID
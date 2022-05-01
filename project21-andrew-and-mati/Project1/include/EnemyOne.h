#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "BillboardedBoundary.h"
#include "Cell.h"
#include "Grid.h"
#include "Thor/Vectors.hpp"
#include "SFML/System.hpp"
#include <SFML/Audio.hpp>

class EnemyOne
{
public:
	EnemyOne();
	EnemyOne(sf::Vector2f t_pos);
	BillboardedBoundary sprite;
	BillboardedBoundary* getSprite();
	sf::RectangleShape topViewRect;
	void setupPath(Cell* playerCell,Grid* grid);
	std::vector<int> path;
	void updatePos(Grid* grid, Cell* oldCell,sf::Vector2f playerPos);
	void runAStar(Grid* grid, const sf::Vector2f& t_playerPos);
	void updateLines(sf::RenderWindow& t_window, Grid* grid);
	bool alive = true;
	int lives = 35;
	void takeDamage();
	void checkForPlayerHit(Cell* PlayerCell, int& t_playeHealth, float dt);

private:
	sf::SoundBuffer enemyHitBuffer;
	sf::Sound enemyHitSound;

	int texindex = 0;
	sf::Vector2f pos = { 400,400 };
	sf::Texture texture;
	bool isMoving = false;
	sf::Vector2f m_vel;
	sf::Vector2f CellPos;
	Cell* currentCell;
	bool foundNextPos = false;
	float speed = 0.35f;
	bool hitPlayer = false;
	sf::Time timeElapsed;
};


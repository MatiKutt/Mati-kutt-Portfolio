#include "EnemyOne.h"

EnemyOne::EnemyOne()
{
	sprite = BillboardedBoundary(pos, 6, 16);

	topViewRect.setFillColor(sf::Color::Transparent);
	topViewRect.setSize(sf::Vector2f(25 ,25));
	topViewRect.setOrigin(sf::Vector2f(topViewRect.getSize().x / 2, topViewRect.getSize().y / 2));
	topViewRect.setOutlineThickness(2);
	topViewRect.setOutlineColor(sf::Color::Yellow);
	topViewRect.setPosition(pos);
}

EnemyOne::EnemyOne(sf::Vector2f t_pos)
{
	pos = t_pos;

	sprite = BillboardedBoundary(pos, 6, 16);

	topViewRect.setFillColor(sf::Color::Transparent);
	topViewRect.setSize(sf::Vector2f(25, 25));
	topViewRect.setOrigin(sf::Vector2f(topViewRect.getSize().x / 2, topViewRect.getSize().y / 2));
	topViewRect.setOutlineThickness(2);
	topViewRect.setOutlineColor(sf::Color::Yellow);
	topViewRect.setPosition(pos);

	enemyHitBuffer.loadFromFile("./recources/SOUNDS/enemyHit.wav");
	enemyHitSound.setBuffer(enemyHitBuffer);
	enemyHitSound.setVolume(40);
}

BillboardedBoundary* EnemyOne::getSprite()
{
	return &sprite;
}

void EnemyOne::setupPath(Cell* playerCell, Grid* grid)
{
	Cell* enemyCell = grid->GetIntersects(pos);

	if (enemyCell != nullptr)
	{
		grid->aStar(enemyCell, playerCell, &path);
	}

	isMoving = true;
}

void EnemyOne::updatePos(Grid* grid, Cell* oldCell, sf::Vector2f playerPos)
{
	if (alive)
	{
		if (oldCell->m_id != grid->at(grid->getCellPlayerIsIn(playerPos))->m_id)
		{
			if (std::find(path.begin(), path.end(), grid->at(grid->getCellPlayerIsIn(playerPos))->m_id) == path.end())
			{
				path.insert(path.begin(), grid->at(grid->getCellPlayerIsIn(playerPos))->m_id);
			}

			oldCell = grid->at(grid->getCellPlayerIsIn(playerPos));
		}

		if (path.size() >= 12)
		{
			isMoving = false;
			foundNextPos = false;

			if (grid->at(grid->getCellPlayerIsIn(playerPos)) != grid->at(grid->getCellPlayerIsIn(pos)))
			{
				runAStar(grid, playerPos);
			}
		}

		if (!path.empty())
		{
			if (isMoving)
			{
				if (!foundNextPos)
				{
					currentCell = grid->at(path.back());

					CellPos = currentCell->center;

					m_vel = (CellPos - pos);
					m_vel = speed * thor::unitVector(m_vel);

					foundNextPos = true;
				}

				pos = pos + m_vel;

				topViewRect.setPosition(pos);
				sprite.updatePos(pos, 32);

				if (thor::length(CellPos - pos) <= 1)
				{
					foundNextPos = false;
					path.pop_back();
				}
			}
		}
		else
		{
			isMoving = false;
			foundNextPos = false;

			if (grid->at(grid->getCellPlayerIsIn(playerPos)) != grid->at(grid->getCellPlayerIsIn(pos)))
			{
				runAStar(grid, playerPos);
			}
		}
	}
}

void EnemyOne::runAStar(Grid* grid, const sf::Vector2f& t_playerPos)
{
	path.clear();
	grid->reset();
	setupPath(grid->at(grid->getCellPlayerIsIn(t_playerPos)), grid);
}

void EnemyOne::updateLines(sf::RenderWindow& t_window, Grid* grid)
{
	sf::VertexArray vertices(sf::LinesStrip);
	
	int count = 0;
	for (auto p : path)
	{
		
		vertices.append(sf::Vertex(grid->at(p)->center, sf::Color::White));
		
		count++;
	}
	vertices.append(pos);
	t_window.draw(vertices);
}

void EnemyOne::takeDamage()
{
	lives--;
	if (lives <= 0)
	{
		alive = false;
	}
}

void EnemyOne::checkForPlayerHit(Cell* PlayerCell, int& t_playeHealth, float dt )
{
	if (timeElapsed.asSeconds() <= 2.0f && hitPlayer == true)
	{
		timeElapsed += sf::seconds(dt);
	}

	if (timeElapsed.asSeconds() >= 2.0f)
	{
		hitPlayer = false;
		timeElapsed = sf::seconds(0);
	}

	for (auto& myCellID : PlayerCell->neighboursids)
	{
		if (currentCell->m_id == myCellID)
		{
			if (hitPlayer == false)
			{
				hitPlayer = true;
				t_playeHealth--;
				enemyHitSound.play();
			}
		}
	}

	if (PlayerCell->m_id == currentCell->m_id)
	{
		if (hitPlayer == false)
		{
			hitPlayer = true;
			t_playeHealth--;
			enemyHitSound.play();
		}
	}
}

#pragma once

#include <SFML/Graphics.hpp>
#include <Thor/Vectors/VectorAlgebra2D.hpp>
#include <Thor/Vectors/PolarVector2.hpp>
#include <Thor/Shapes/Arrow.hpp>
#include "Boundary.h"
#include <iostream>
#include "BillboardedBoundary.h"
#include "EnemyOne.h"

class Ray
{
public:
	sf::VertexArray lines { sf::Lines, 2 }; // drawable element
	sf::Vector2f intersectionPoint; // points of intersection, used for maths and drawing the rays from top down
	sf::Vector2f closestIntersect; // closest point of intersection, currently unused but will be needed for multiple walls
	
	bool Enemy = false;
	bool hitSprite = false;
	bool hitEnemy = false;
	int textureToRender = 0; // this value gets pulled from the barrier the ray collides with,determines what texture gets drawn
	int enemyToRender = 0;
	int spriteToRender = 0; // this value gets pulled from sprite when intersection is found
	sf::Vector2f spriteHitDistance = sf::Vector2f(INFINITY,INFINITY);
	sf::Vector2f enemyHitDistance = sf::Vector2f(INFINITY, INFINITY);

	bool intersects = false; // does the ray intersect?
	sf::Color rayColor;
	Ray(float angle);

	void update(sf::RenderWindow& t_window, std::vector<Boundary> bounds);
	
	void draw(sf::RenderWindow& t_window);
	void storeWall(Boundary& t_wall);
	void storeSprite(BillboardedBoundary& t_sprite);
	void storeEnemy(EnemyOne& t_sprite);

	Boundary* getWall();
	BillboardedBoundary* getSprite();
	EnemyOne* getEnemy();

	sf::Vector2f cast(Boundary bound);
	sf::Vector2f castAtSprite(BillboardedBoundary* bound);
	sf::Vector2f castAtEnemy(EnemyOne *Enemy);

	sf::Vector2f source;// this is simply a storage for where the ray is emitting from
	sf::Vector2f m_dir; // direction vector, for all intents and purposes, this is the "true" ray vector as it determines the direction.

private:
	Boundary* StoredHitWall;
	BillboardedBoundary* storedSprite;
	EnemyOne* storedEnemy;
};


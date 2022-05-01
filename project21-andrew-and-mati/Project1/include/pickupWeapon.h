#pragma once
#include "BillboardedBoundary.h"
#include "Cube.h"
#include "SFML/Graphics.hpp"
//#include "Player.h"
 enum class pickupType
{
	 Weapon,
	 Health,
	 Ammo,
	 Pint,
};


class pickupWeapon
{
public:
	pickupWeapon(sf::Vector2f t_pos, pickupType t_type);
	//void update(Player& t_player);
	void draw(sf::RenderWindow& t_mapWindow);
	void rotatePickup();
	int m_sprite = 7;
	BillboardedBoundary* spriteBound;
	Cube* collider;
	pickupType type;

};


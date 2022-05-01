#include "pickupWeapon.h"

pickupWeapon::pickupWeapon(sf::Vector2f t_pos, pickupType t_type)
{
	type = t_type;

	switch (t_type)
	{
	default:
		break;
	case pickupType::Ammo:
		m_sprite = 7;
		break;
	case pickupType::Health:
		m_sprite = 9;
		break;

	case pickupType::Pint:
		m_sprite = 8;
		break;

	case pickupType::Weapon:
		m_sprite = 7;
		break;


	}

	collider = new Cube(t_pos, m_sprite);
	spriteBound = new BillboardedBoundary(t_pos, m_sprite, 16,Type::Rotating);

}

void pickupWeapon::draw(sf::RenderWindow& t_mapWindow)
{
	t_mapWindow.draw(this->collider->body);
	this->spriteBound->draw(t_mapWindow);
}


//void pickupWeapon::update(Player& t_player)
//{
//
//
//}

void pickupWeapon::rotatePickup()
{
	
}

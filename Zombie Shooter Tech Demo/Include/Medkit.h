#pragma once
#include "Consumable.h"
class Medkit :
	public Consumable
{
public:
	Medkit(float t_scale, std::string t_fileName, sf::Vector2f t_pos) : Consumable(t_scale, t_fileName, t_pos)
	{

	};
	void pickup(Player &t_player);

};


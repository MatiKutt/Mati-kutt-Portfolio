#pragma once
#include "Consumable.h"
class Ammocrate :
	public Consumable
{
public:
	Ammocrate(float t_scale, std::string t_fileName, sf::Vector2f t_pos) : Consumable(t_scale, t_fileName, t_pos)
	{
	};
	static int amountConsumables;
	void pickup(Player& t_player);
	//void setup(sf::Vector2f t_position, std::string t_fileNameTexture = "ammocrate.png");
};


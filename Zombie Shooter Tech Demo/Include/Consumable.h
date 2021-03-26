
#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"

class Consumable
{
public:
	Consumable(float t_scale, std::string t_fileName, sf::Vector2f t_pos) : scale(t_scale), fileName(t_fileName), position(t_pos) 
	{
		if (!this->consumableTexture.loadFromFile("ART/" + t_fileName))
		{
			std::cout << "error loading Consumable File" <<std::endl;
		}
		this->consumableSprite.setTexture(consumableTexture);
		this->consumableSprite.setScale(sf::Vector2f(scale, scale));
		this->consumableSprite.setPosition(t_pos); 
		
	};
	

	virtual void        draw(sf::RenderWindow& t_window);
	virtual void        pickup(Player t_player);
	sf::Vector2f        getPosition();
	bool                active = true;
	sf::Texture         consumableTexture;
	sf::Sprite          consumableSprite;
	std::string         fileName{};
	sf::Vector2f        position;
	float               scale{};
};


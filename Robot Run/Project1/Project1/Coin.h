//Mati Kutt
//https://instituteoftechnol663-my.sharepoint.com/:v:/g/personal/c00250720_itcarlow_ie/ET7MfdaXqgBPsPlBpAkTy1oBANNCEDhLj3D4wRxUZSLTHQ?email=Noel.OHara%40itcarlow.ie&e=8TzVXg
#pragma once
#include <SFML/Graphics.hpp>
class Coin
{
public:
	sf::RectangleShape coinBody;
	sf::Sprite coinSprite;
	sf::Texture coinTexture;
	bool active;
	void draw(sf::RenderWindow &m_window);
	void init(sf::Vector2f m_position);
	
};


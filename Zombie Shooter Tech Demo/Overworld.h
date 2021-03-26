#pragma once
#include <SFML/Graphics.hpp>
class Overworld
{
public:
	sf::Texture playerCarTexture;
	sf::Sprite  playerSpriteTexture;

	sf::Texture overWorldMap;
	sf::Sprite  overWorldSprite;




	void             update(sf::Time);
	void             render(sf::RenderWindow m_window);
	void             checkPickup();
	void			 checkGameOver();
	sf::Vector2f     viewMove{ 0,0 };
	sf::Sprite       background;
	sf::Texture      backgroundtexture;

};



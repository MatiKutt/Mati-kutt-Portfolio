#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "GLOBALS.h"

class DeathScreen
{
public:

	DeathScreen();
	void initalise();
	void render(sf::RenderWindow& m_window);
	void processInput(sf::Event t_event);

private:
	//variables for background texture and sprite
	sf::Texture m_BGTexture;
	sf::Sprite m_BGSprite;

	//variables for play texture and sprite
	sf::Texture m_playButtonText;
	sf::Sprite m_playButtonSprite;

	//variables for exit/quit button texture and sprite
	sf::Texture m_exitButtonText;
	sf::Sprite m_exitButtonSprite;

	//variables for logo texture and sprite
	sf::Texture m_logoText;
	sf::Sprite m_logoSprite;

	sf::Vector2f mp; // holds mouseposition
};


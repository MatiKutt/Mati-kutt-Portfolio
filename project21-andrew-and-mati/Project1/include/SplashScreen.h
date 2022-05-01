#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include "GLOBALS.h"

class SplashScreen
{
public:

	SplashScreen();
	void initalise(sf::Font& t_font);
	void render(sf::RenderWindow& m_window);
	void processInput(sf::Event t_event);

private:
	sf::Text m_message; // holds splashscrren main body of text
	sf::Texture m_BGTexture; // holds background texture
	sf::Sprite m_BGSprite; // holds background sprite for texture

};


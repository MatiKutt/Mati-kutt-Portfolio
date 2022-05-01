#pragma once
#include <SFML/Graphics.hpp>
#include "GLOBALS.h"
#include "Player.h"
class UI
{
public:
	UI()
	{
		weaponSprite.setScale(sf::Vector2f(2, 2));
		weaponSprite.setPosition(xRes / 2, yRes / 2.2);




		bloodTexture.loadFromFile("./recources/TEXTURES/blood.png");
		bloodSprite.setTexture(bloodTexture);



		weaponTextures[0].loadFromFile("./recources/TEXTURES/WeaponSprites/Rifle.png");
		weaponSprite.setTexture(weaponTextures[0]);
		UITexture.loadFromFile("./recources/TEXTURES/UI2.png");
		UISprite.setTexture(UITexture);

		UIFont.loadFromFile("./recources/FONTS/ARCADECLASSIC.ttf");
		ammoText.setFont(UIFont);
		ammoText.setPosition(75, 538);

		examineText.setFont(UIFont);
		examineText.setPosition(10, 10);
		examineText.setString("Nothing");
		
		healthText.setFont(UIFont);
		healthText.setPosition(210, 538);

		pintsText.setFont(UIFont);
		pintsText.setPosition(610, 540);

		crosshairTexture.loadFromFile("./recources/TEXTURES/crosshair.png");
		crosshairSprite.setTexture(crosshairTexture);
		crosshairSprite.setScale(0.25f, 0.25f);
		crosshairSprite.setOrigin(sf::Vector2f(crosshairSprite.getGlobalBounds().width / 2, crosshairSprite.getGlobalBounds().height / 2));
		crosshairSprite.setPosition(xRes / 2, yRes / 2.2);


		examineTextsArr[0] = "A cobblestone wall";
		examineTextsArr[1] = "A red brick wall";
		examineTextsArr[2] = "A scary red brick wall";
		examineTextsArr[3] = "A plain white wall";
		examineTextsArr[4] = "Some kind of metal door";
		examineTextsArr[5] = "A tree";
		examineTextsArr[6] = "A large enemy";
		examineTextsArr[7] = "A crate of weapons";
		examineTextsArr[8] = "A crate of pints";
		
	}

	sf::Texture weaponTextures[1];
	sf::Sprite weaponSprite;
	sf::Sprite bloodSprite;
	sf::Texture bloodTexture;
	sf::Texture UITexture;
	sf::Sprite UISprite;
	std::string examineTextsArr[9];
	sf::Texture crosshairTexture;
	sf::Sprite crosshairSprite;
	sf::Font UIFont;
	sf::Text ammoText;
	sf::Text healthText;
	sf::Text pintsText;
	sf::Text examineText;
	void updateExamineText(Player& m_player);
	void updateHUDText(Player& m_player);
	void draw(sf::RenderWindow& m_window, Player& m_player);
};


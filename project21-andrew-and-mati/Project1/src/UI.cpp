#include "..\include\UI.h"

void UI::draw(sf::RenderWindow& m_window, Player& m_player)
{

	m_window.draw(this->weaponSprite);
	m_window.draw(bloodSprite);
	m_window.draw(this->UISprite);
	m_window.draw(this->crosshairSprite);
	m_window.draw(ammoText);
	m_window.draw(examineText);
	m_window.draw(healthText);
	m_window.draw(pintsText);
	if (m_player.rateOfFireLimit == m_player.ROFTIMEOUTCAP)
	{
		weaponSprite.setScale(2, 2);
	}
	else
	{
		weaponSprite.setScale(3, 3);
	}


	

	updateExamineText(m_player);
	
	updateHUDText(m_player);

	
}
void UI::updateExamineText(Player& m_player)
{

	Ray* middleRay = m_player.getrays()[m_player.getrays().size() / 2];
	if (middleRay->intersectionPoint != sf::Vector2f(INFINITY, INFINITY))
	{
		int raySpriteNumber = middleRay->getWall()->texture;

		examineText.setString(examineTextsArr[raySpriteNumber]);
	}
	else
	{
		examineText.setString("");
	}
}
void UI::updateHUDText(Player& m_player)
{
	pintsText.setString(std::to_string(m_player.getPints()));
	healthText.setString(std::to_string(m_player.getHealth()));
	ammoText.setString(std::to_string(m_player.getAmmo()));

	if (m_player.getHealth() >= 7)
	{
		bloodSprite.setColor(sf::Color(255, 255, 255, 0));
	}
	else if (m_player.getHealth() == 6)
	{
		bloodSprite.setColor(sf::Color(255, 255, 255, 15));
	}
	else if (m_player.getHealth() == 5)
	{
		bloodSprite.setColor(sf::Color(255, 255, 255, 40));
	}
	else if (m_player.getHealth() == 4)
	{
		bloodSprite.setColor(sf::Color(255, 255, 255, 60));
	}
	else if (m_player.getHealth() == 3)
	{
		bloodSprite.setColor(sf::Color(255, 255, 255, 80));
	}
	else if (m_player.getHealth() == 2)
	{
		bloodSprite.setColor(sf::Color(255, 255, 255, 150));
	}
	else if (m_player.getHealth() == 1)
	{
		bloodSprite.setColor(sf::Color(255, 255, 255, 255));
	}
}
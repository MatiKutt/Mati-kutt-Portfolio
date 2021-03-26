//https://instituteoftechnol663-my.sharepoint.com/:v:/g/personal/c00250720_itcarlow_ie/ET7MfdaXqgBPsPlBpAkTy1oBANNCEDhLj3D4wRxUZSLTHQ?email=Noel.OHara%40itcarlow.ie&e=8TzVXg
//Mati Kutt
#include "Coin.h"

void Coin::draw(sf::RenderWindow &m_window)
{
	m_window.draw(coinSprite);
	//m_window.draw(coinBody);
}

void Coin::init(sf::Vector2f m_position)
{
	coinBody.setSize(sf::Vector2f(25, 25));
	coinTexture.loadFromFile("coin.png");
	coinSprite.setTexture(coinTexture);
	active = true;
	coinBody.setPosition(m_position);
}

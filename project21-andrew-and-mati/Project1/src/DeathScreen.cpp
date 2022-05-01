#include "DeathScreen.h"
#include "Game.h"

DeathScreen::DeathScreen()
{
}

void DeathScreen::initalise()
{
	if (!m_BGTexture.loadFromFile("./recources/TEXTURES/brks_2.png"))
	{
		std::cout << "Error with Deathscreen background image" << std::endl;
	}
	m_BGSprite.setScale(8, 8);
	m_BGTexture.setRepeated(true);
	m_BGSprite.setTexture(m_BGTexture);
	m_BGSprite.setTextureRect(sf::IntRect(0, 0, xRes, yRes));

	if (!m_playButtonText.loadFromFile("./recources/TEXTURES/playButton.png"))
	{
		std::cout << "Error with Play button image" << std::endl;
	}
	m_playButtonSprite.setScale(0.3f, 0.3f);
	m_playButtonSprite.setTexture(m_playButtonText);
	m_playButtonSprite.setOrigin(m_playButtonSprite.getLocalBounds().width / 2, m_playButtonSprite.getLocalBounds().height / 2);
	m_playButtonSprite.setPosition(xRes / 2, xRes / 2 - 75);

	if (!m_exitButtonText.loadFromFile("./recources/TEXTURES/Button_Quit.png"))
	{
		std::cout << "Error with Quit button image" << std::endl;
	}
	m_exitButtonSprite.setScale(0.3f, 0.3f);
	m_exitButtonSprite.setTexture(m_exitButtonText);
	m_exitButtonSprite.setOrigin(m_exitButtonSprite.getLocalBounds().width / 2, m_exitButtonSprite.getLocalBounds().height / 2);
	m_exitButtonSprite.setPosition(xRes / 2, xRes / 2 + 100.0f);

	if (!m_logoText.loadFromFile("./recources/TEXTURES/DeathTexture.png"))
	{
		std::cout << "Error with Deat texture image" << std::endl;
	}
	m_logoSprite.setTexture(m_logoText);
	m_logoSprite.setOrigin(m_logoSprite.getLocalBounds().width / 2, m_logoSprite.getLocalBounds().height / 2);
	m_logoSprite.setScale(0.75f, 0.75f);
	m_logoSprite.setPosition(xRes / 2, xRes / 2 - 250.0f);
}

void DeathScreen::render(sf::RenderWindow& m_window)
{
	//set mouse position for input for buttons
	mp.x = sf::Mouse::getPosition(m_window).x;
	mp.y = sf::Mouse::getPosition(m_window).y;

	//draw nessesary sprites
	m_window.draw(m_BGSprite);
	m_window.draw(m_exitButtonSprite);
	m_window.draw(m_playButtonSprite);
	m_window.draw(m_logoSprite);
}

void DeathScreen::processInput(sf::Event t_event)
{
	if (m_playButtonSprite.getGlobalBounds().contains(mp))
	{
		m_playButtonSprite.setScale(0.5f, 0.5f);

		if (t_event.type == sf::Event::MouseButtonReleased && t_event.mouseButton.button == sf::Mouse::Left)
		{
			Game::currentState = GameState::ResetGame;
		}
	}
	else
	{
		m_playButtonSprite.setScale(0.3f, 0.3f);
	}

	if (m_exitButtonSprite.getGlobalBounds().contains(mp))
	{
		m_exitButtonSprite.setScale(0.5f, 0.5f);

		if (t_event.type == sf::Event::MouseButtonReleased && t_event.mouseButton.button == sf::Mouse::Left)
		{
			Game::currentState = GameState::MainMenu;
		}
	}
	else
	{
		m_exitButtonSprite.setScale(0.3f, 0.3f);
	}
}

#include "SplashScreen.h"
#include "Game.h"

SplashScreen::SplashScreen()
{

}

/// <summary>
/// sets up all of the textures and loads them into sprite objects
/// </summary>
/// <param name="t_font"></param>
void SplashScreen::initalise(sf::Font& t_font)
{
	if (!m_BGTexture.loadFromFile("./recources/TEXTURES/Texture.png"))
	{
		std::cout << "Error with Splashscreen background image" << std::endl;
	}

	m_BGTexture.setRepeated(true);
	m_BGSprite.setScale(8, 8);
	m_BGSprite.setTexture(m_BGTexture);
	m_BGSprite.setTextureRect(sf::IntRect(0, 0,xRes, yRes));
	
	m_message.setFont(t_font);
	m_message.setCharacterSize(70.0f);
	m_message.setString("Space bar' to continue");
	m_message.setOrigin(m_message.getLocalBounds().width / 2, m_message.getLocalBounds().height / 2);
	m_message.setPosition(xRes / 2, yRes / 2);
}

/// <summary>
/// function for rendering each object required for the splashscreen
/// </summary>
/// <param name="m_window"></param>
void SplashScreen::render(sf::RenderWindow& m_window)
{
	m_window.draw(m_BGSprite);
	m_window.draw(m_message);
}

/// <summary>
/// checks for a input, this being space key and changes gamestate accordingly
/// </summary>
/// <param name="t_event"></param>
void SplashScreen::processInput(sf::Event t_event)
{
	if (sf::Event::KeyPressed == t_event.type)
	{
		if (sf::Keyboard::Space == t_event.key.code)
		{
			Game::currentState = GameState::MainMenu;
		}
	}
}

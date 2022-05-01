#include "MainMenu.h"
#include "Game.h"

/// <summary>
/// Default constructor
/// </summary>
MainMenu::MainMenu()
{

}

/// <summary>
/// sets up all of the textures and loads them into sprite objects
/// </summary>
/// <param name="t_font"></param>
void MainMenu::initalise()
{
	if (!m_BGTexture.loadFromFile("./recources/TEXTURES/Texture2.png"))
	{
		std::cout << "Error with Splashscreen background image" << std::endl;
	}
	m_BGSprite.setScale(8, 8);
	m_BGTexture.setRepeated(true);
	m_BGSprite.setTexture(m_BGTexture);
	m_BGSprite.setTextureRect(sf::IntRect(0, 0, xRes , yRes));

	if (!m_playButtonText.loadFromFile("./recources/TEXTURES/playButton.png"))
	{
		std::cout << "Error with Play button image" << std::endl;
	}
	m_playButtonSprite.setScale(0.5f, 0.5f);
	m_playButtonSprite.setTexture(m_playButtonText);
	m_playButtonSprite.setOrigin(m_playButtonSprite.getLocalBounds().width / 2, m_playButtonSprite.getLocalBounds().height / 2);
	m_playButtonSprite.setPosition(xRes / 2, xRes / 2 - 190);



	if (!m_levelEditorText.loadFromFile("./recources/TEXTURES/levelButton.png"))
	{
		std::cout << "Error with level editor image" << std::endl;
	}
	m_levelEditorSprite.setScale(0.5f, 0.5f);
	m_levelEditorSprite.setTexture(m_levelEditorText);
	m_levelEditorSprite.setOrigin(m_levelEditorSprite.getLocalBounds().width / 2, m_levelEditorSprite.getLocalBounds().height / 2);
	m_levelEditorSprite.setPosition(xRes / 2, xRes / 2 - 50);




	if (!m_exitButtonText.loadFromFile("./recources/TEXTURES/Button_Quit.png"))
	{
		std::cout << "Error with Quit button image" << std::endl;
	}
	m_exitButtonSprite.setScale(0.3f, 0.3f);
	m_exitButtonSprite.setTexture(m_exitButtonText);
	m_exitButtonSprite.setOrigin(m_exitButtonSprite.getLocalBounds().width / 2, m_exitButtonSprite.getLocalBounds().height / 2);
	m_exitButtonSprite.setPosition(xRes / 2, xRes / 2 + 100.0f);




	if (!m_logoText.loadFromFile("./recources/TEXTURES/Game_Logo.png"))
	{
		std::cout << "Error with Logo image" << std::endl;
	}
	m_logoSprite.setTexture(m_logoText);
	m_logoSprite.setOrigin(m_logoSprite.getLocalBounds().width / 2, m_logoSprite.getLocalBounds().height / 2);
	m_logoSprite.setPosition(xRes / 2, xRes / 2 - 300.0f);
}

/// <summary>
/// function for rendering, sprites related to main menu and getting mouseposition in relation to window
/// </summary>
/// <param name="m_window"></param>
void MainMenu::render(sf::RenderWindow& m_window)
{
	//set mouse position for input for buttons
	mp.x = sf::Mouse::getPosition(m_window).x;
	mp.y = sf::Mouse::getPosition(m_window).y;

	//draw nessesary sprites
	m_window.draw(m_BGSprite);
	m_window.draw(m_exitButtonSprite);
	m_window.draw(m_levelEditorSprite);
	m_window.draw(m_playButtonSprite);
	m_window.draw(m_logoSprite);
}

/// <summary>
/// function that procceses mouse position and checks for a left click on a button, and changes game state accordingly
/// </summary>
/// <param name="t_event"></param>
void MainMenu::processInput(sf::Event t_event)
{
	if (m_playButtonSprite.getGlobalBounds().contains(mp)) 
	{
		m_playButtonSprite.setScale(0.6f, 0.6f);

		if (t_event.type == sf::Event::MouseButtonReleased && t_event.mouseButton.button == sf::Mouse::Left)
		{
			Game::currentState = GameState::Game;
		}
	}
	else 
	{
		m_playButtonSprite.setScale(0.5f, 0.5f);
	}

	if (m_exitButtonSprite.getGlobalBounds().contains(mp))
	{
		m_exitButtonSprite.setScale(0.4f, 0.4f);

		if (t_event.type == sf::Event::MouseButtonReleased && t_event.mouseButton.button == sf::Mouse::Left)
		{
			Game::currentState = GameState::Endgame;
		}
	}
	else 
	{
		m_exitButtonSprite.setScale(0.3f, 0.3f);
	}

	if (m_levelEditorSprite.getGlobalBounds().contains(mp))
	{
		m_levelEditorSprite.setScale(0.4f, 0.4f);

		if (t_event.type == sf::Event::MouseButtonReleased && t_event.mouseButton.button == sf::Mouse::Left)
		{
			Game::currentState = GameState::LevelEdit;
			std::cout << "level edit pressed" << std::endl;
		}
	}
	else
	{
		m_levelEditorSprite.setScale(0.3f, 0.3f);
	}

}

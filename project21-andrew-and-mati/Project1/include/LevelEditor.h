#pragma once
#include "Grid.h"
#include <SFML/Graphics.hpp>
#include "GLOBALS.h"
#include<string>
#include <iostream>
#include "LevelLoader.h"

class LevelEditor
{
public:
	LevelEditor() 
	{
		editorGrid.setupGrid();
		
		for (int index = 0; index < editorGrid.TotalCells; index++)
		{
			blocks.push_back(0);
		}

		if (!loadButtonTexture.loadFromFile("./recources/TEXTURES/LoadButton.png"))
		{
			std::cout << "Error with Load button image" << std::endl;
		}

		loadButtonSprite.setScale(0.2f, 0.2f);
		loadButtonSprite.setTexture(loadButtonTexture);
		loadButtonSprite.setOrigin(loadButtonSprite.getLocalBounds().width / 2, loadButtonSprite.getLocalBounds().height / 2);
		loadButtonSprite.setPosition(xRes - 75, yRes / 2 + 200.0f);

		if (!saveButtonTexture.loadFromFile("./recources/TEXTURES/SaveButton.png"))
		{
			std::cout << "Error with Save button image" << std::endl;
		}

		saveButtonSprite.setScale(0.2f, 0.2f);
		saveButtonSprite.setTexture(saveButtonTexture);
		saveButtonSprite.setOrigin(saveButtonSprite.getLocalBounds().width / 2, saveButtonSprite.getLocalBounds().height / 2);
		saveButtonSprite.setPosition(xRes - 75, yRes / 2 + 100.0f);

		if (!playButtonTexture.loadFromFile("./recources/TEXTURES/playButton.png"))
		{
			std::cout << "Error with play button image" << std::endl;
		}

		playButtonSprite.setScale(0.2f, 0.2f);
		playButtonSprite.setTexture(playButtonTexture);
		playButtonSprite.setOrigin(playButtonSprite.getLocalBounds().width / 2, playButtonSprite.getLocalBounds().height / 2);
		playButtonSprite.setPosition(xRes - 75, yRes / 2 - 100);

		if (!quitButtonTexture.loadFromFile("./recources/TEXTURES/Button_Quit.png"))
		{
			std::cout << "Error with quit button image" << std::endl;
		}

		quitButtonSprite.setScale(0.2f, 0.2f);
		quitButtonSprite.setTexture(quitButtonTexture);
		quitButtonSprite.setOrigin(quitButtonSprite.getLocalBounds().width / 2, quitButtonSprite.getLocalBounds().height / 2);
		quitButtonSprite.setPosition(xRes - 75, yRes / 2);


		if (!font.loadFromFile("./recources/FONTS/arial.ttf"))
		{
			std::cout << "Error with font" << std::endl;
		}

		text.setFont(font);
		text.setString("Green: BB tree\nRed: enemy\nBrown: ammo\nWhite: health\ngrey: pint\nPink: V door\nPurple: H door\nCyan: Player");
		text.setScale(0.45f, 0.45f);
		text.setOrigin(text.getLocalBounds().width / 2, text.getLocalBounds().height / 2);
		text.setPosition(xRes - 75, 80);


	};

	void draw(sf::RenderWindow& t_window);
	void update(sf::Event t_event, sf::RenderWindow& t_window,sf::Texture t_textures[]);

	sf::Texture loadButtonTexture;
	sf::Sprite loadButtonSprite;

	sf::Texture saveButtonTexture;
	sf::Sprite saveButtonSprite;

	sf::Texture playButtonTexture;
	sf::Sprite playButtonSprite;

	sf::Texture quitButtonTexture;
	sf::Sprite quitButtonSprite;

	std::vector<int> blocks;

	LevelData t_lev;

	void savegame();
	void loadGame(sf::Texture t_textures[]);
	Grid editorGrid;

	sf::Font font;
	sf::Text text;
};


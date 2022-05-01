#include "LevelEditor.h"
#include "Game.h"

void LevelEditor::draw(sf::RenderWindow& t_window)
{
	editorGrid.draw(t_window);
	t_window.draw(loadButtonSprite);
	t_window.draw(saveButtonSprite);
	t_window.draw(playButtonSprite);
	t_window.draw(quitButtonSprite);
	t_window.draw(text);
}


void LevelEditor::update(sf::Event t_event, sf::RenderWindow& t_window, sf::Texture t_textures[])
{
	sf::Vector2f mp;

	mp.x = sf::Mouse::getPosition(t_window).x;
	mp.y = sf::Mouse::getPosition(t_window).y;

	if (loadButtonSprite.getGlobalBounds().contains(mp))
	{
		loadButtonSprite.setScale(0.25f, 0.25f);

		if (t_event.type == sf::Event::MouseButtonReleased && t_event.mouseButton.button == sf::Mouse::Left)
		{
			std::cout << "Load custom level" << std::endl;

			t_lev.m_blockType.clear();

			editorGrid.reset();
			blocks.clear();

			for (int index = 0; index < editorGrid.TotalCells; index++)
			{
				blocks.push_back(0);
			}

			loadGame(t_textures);
		}
	}
	else
	{
		loadButtonSprite.setScale(0.2f, 0.2f);
	}

	if (saveButtonSprite.getGlobalBounds().contains(mp))
	{
		saveButtonSprite.setScale(0.25f, 0.25f);

		if (t_event.type == sf::Event::MouseButtonReleased && t_event.mouseButton.button == sf::Mouse::Left)
		{
			std::cout << "Save custom level" << std::endl;
			savegame();
		}
	}
	else
	{
		saveButtonSprite.setScale(0.2f, 0.2f);
	}

	if (playButtonSprite.getGlobalBounds().contains(mp))
	{
		playButtonSprite.setScale(0.25f, 0.25f);

		if (t_event.type == sf::Event::MouseButtonReleased && t_event.mouseButton.button == sf::Mouse::Left)
		{
			std::cout << "play custom level" << std::endl;
			mapBlock block;
			t_lev.m_blockType.clear();
			t_lev.m_blockType.push_back(block);
			for (int index = 0; index < editorGrid.TotalCells; index++)
			{
				t_lev.m_blockType.at(0).block.push_back(blocks.at(index));
			}

			Game::currentState = GameState::CustomMapGame;
		}
	}
	else
	{
		playButtonSprite.setScale(0.2f, 0.2f);
	}

	if (quitButtonSprite.getGlobalBounds().contains(mp))
	{
		quitButtonSprite.setScale(0.25f, 0.25f);

		if (t_event.type == sf::Event::MouseButtonReleased && t_event.mouseButton.button == sf::Mouse::Left)
		{
			std::cout << "quit custom level" << std::endl;
			
			Game::currentState = GameState::MainMenu;
			
			t_lev.m_blockType.clear();

			editorGrid.reset();
			blocks.clear();
			
			for (int index = 0; index < editorGrid.TotalCells; index++)
			{
				blocks.push_back(0);
			}
		}
	}
	else
	{
		quitButtonSprite.setScale(0.2f, 0.2f);
	}

	if (t_event.type == sf::Event::MouseButtonReleased && t_event.mouseButton.button == sf::Mouse::Left)
	{
		for (int index = 0; index < editorGrid.TotalCells; index++)
		{
			if (editorGrid.at(index)->cellBody.getGlobalBounds().contains(mp))
			{
				int currentTexture = blocks.at(index);

				currentTexture++;

				if (currentTexture >= 13) 
				{
					currentTexture = 0;
				}

				blocks.at(index) = currentTexture;

				if (currentTexture == 0) 
				{
					editorGrid.at(index)->cellBody.setFillColor(sf::Color::Transparent);
					editorGrid.at(index)->cellBody.setTexture(NULL);
				}
				else
				{
					editorGrid.at(index)->cellBody.setFillColor(sf::Color::White);
					editorGrid.at(index)->cellBody.setTexture(&t_textures[(currentTexture - 1)], true);
				}

				break;
			}
		}
	}
}

void LevelEditor::savegame()
{
	std::string saveFileName;

	std::cout << "Just the level name, no need for file extensions!, saves are storges in CUSTOMMAPS/" << std::endl;

	std::cin >> saveFileName;

	std::ofstream myfile("CUSTOMMAPS/" + saveFileName + ".yaml");

	if (myfile.is_open())
	{
		myfile << "map:\n    - map: [";

		for (int index = 0; index < editorGrid.TotalCells; index++)
		{
			if (index != editorGrid.TotalCells - 1)
			{
				myfile << std::to_string(blocks.at(index)) + ", ";
			}
			else 
			{
				myfile << std::to_string(blocks.at(index));
			}
		}
		
		myfile << "]";

		myfile.close();

		std::cout << "Saved Map!" << std::endl;
	}
	else
	{
		std::cout << "Unable to save file" << std::endl;
	}


}

void LevelEditor::loadGame(sf::Texture t_textures[])
{
	std::string saveFileName;

	std::cout << "Just the level name, no need for file extensions!, saves are stored in CUSTOMMAPS/ !" << std::endl;

	std::cin >> saveFileName;

	try
	{
		LevelLoader::loadCustomMap(saveFileName, t_lev);
	}
	catch (std::exception& e)
	{
		std::cout << "Level Loading failure." << std::endl;
		std::cout << e.what() << std::endl;
		throw e;
	}

	blocks.clear();

	int index = 0;

	for (int vec : t_lev.m_blockType.at(0).block)
	{
		if (vec == 0)
		{
			editorGrid.at(index)->cellBody.setFillColor(sf::Color::Transparent);
			editorGrid.at(index)->cellBody.setTexture(NULL);
		}
		else
		{
			editorGrid.at(index)->cellBody.setFillColor(sf::Color::White);
			editorGrid.at(index)->cellBody.setTexture(&t_textures[(vec - 1)]);
		}

		blocks.push_back(vec);

		index++;
	}

	std::cout << "Loaded Map!" << std::endl;
}

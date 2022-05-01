#include "Game.h"
#include <algorithm>
#include <time.h>
#include <random>
#include "imgui.h"
#include "imgui-SFML.h"

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-main-d.lib")
#pragma comment(lib,"sfml-network-d.lib") 

#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-main.lib")
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#pragma comment(lib,"libyaml-cppmdd") 

Game::Game()
	: m_window{ sf::VideoMode{640, 640}, "SMFL Game" } ,
      castWindow{sf::VideoMode{xRes, yRes}, "Totally two dimensional",sf::Style::Default, sf::ContextSettings::ContextSettings(0,0,1,1,1,0,false)}
{
	srand(time(NULL));
#ifdef _DEBUG
	printf("RUNNING DEBUG BUILD \n");
#else
	printf("Running... this is a release build. \n");
#endif

	debugText.setFont(font);
	debugText.setString("DEBUG MODE ON");
	debugText.setScale(0.5f,0.5f);

	ImGui::SFML::Init(m_window);

	mainMusicBuffer.loadFromFile("./recources/SOUNDS/music.wav");
	mainMusic.setBuffer(mainMusicBuffer);
	mainMusic.setLoop(true);
	mainMusic.setVolume(5);
	mainMusic.play();
	
	if (!font.loadFromFile("./recources/FONTS/arial.ttf"))
	{
		std::cout << "Error with font" << std::endl;
	}
	
	ss.initalise(font);
	mm.initalise();
	ds.initalise();

	loadLevel(false);
}

GameState Game::currentState = GameState::SplashScreen;

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.0f);
	while (m_window.isOpen())
	{
		processEvents();
		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timePerFrame)
		{
			
			timeSinceLastUpdate -= timePerFrame;
			processEvents();
			update(timePerFrame);
		}
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;

	while (castWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			castWindow.close();
		
		}

		switch (currentState)
		{
		default:
			break;
		case GameState::SplashScreen:
			ss.processInput(event);
			break;
		case GameState::MainMenu:
			mm.processInput(event);
			break;
		case GameState::Death:
			ds.processInput(event);
			break;
		case GameState::LevelEdit:
			editor.update(event, castWindow, texturesForEditor);
			break;
		}
	}


	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();

		}
		ImGui::SFML::ProcessEvent(event);
	}
}

void Game::drawGame()
{
	if (drawBackgroundSprite)
	{
		castWindow.draw(backgroundSprite);
	}
	//castWindow.draw(ceiling);

	for (int i = 0; i < player.getrays().size(); i++)
	{
		view[i]->setTexture(nullptr);
		spritesView[i]->setTexture(nullptr);
		enemyView[i]->setTexture(nullptr);

		
		drawAndTextureWalls(i);

		drawAndTextureSprites(i);

		drawAndTextureEnemies(i);

		
	}

	sf::Vector2f dir = player.getrays().at((xRes / 5) / 2)->m_dir; // gets the center ray of the player, since each ray corresponds to a rect of width 5, we must first divide by 5 and THEN 2

	for (auto &sprite : sprites)
	{
		sprite->updateV3(player.getPosition());
	}
	if (player.flashOn)
	{
		castWindow.draw(player.flashSprite);
	}

	playerUI.draw(castWindow,player);

#ifdef _DEBUG
	drawDebug();

#endif
}

void Game::loadLevel(bool isCustomMap)
{
	walls.clear();
	sprites.clear();
	cubes.clear();
	pickups.clear();
	view.clear();
	spritesView.clear();
	enemyView.clear();
	enemyTypeOne.clear();

	player.health = 7;
	player.refillAmmo();

	if (!isCustomMap)
	{
		try
		{
			LevelLoader::load(currentLevel, m_level);
		}
		catch (std::exception& e)
		{
			std::cout << "Level Loading failure." << std::endl;
			std::cout << e.what() << std::endl;
			throw e;
		}
	}


	for (int i = 0; i < xRes / 5; i++)
	{
		sf::RectangleShape* rect = new sf::RectangleShape;
		rect->setSize(sf::Vector2f(5, 200));
		rect->setOrigin(rect->getSize().x / 2, rect->getSize().y / 2);
		rect->setPosition(i * 5, yRes / 2);
		rect->setFillColor(sf::Color::White);
		view.push_back(rect);
	}

	for (int i = 0; i < xRes / 5; i++)
	{
		sf::RectangleShape* rect = new sf::RectangleShape;
		rect->setSize(sf::Vector2f(5, 200));
		rect->setOrigin(rect->getSize().x / 2, rect->getSize().y / 2);
		rect->setPosition(i * 5, yRes / 2);
		rect->setFillColor(sf::Color::White);
		spritesView.push_back(rect);
	}

	for (int i = 0; i < xRes / 5; i++)
	{
		sf::RectangleShape* rect = new sf::RectangleShape;
		rect->setSize(sf::Vector2f(5, 200));
		rect->setOrigin(rect->getSize().x / 2, rect->getSize().y / 2);
		rect->setPosition(i * 5, yRes / 2);
		rect->setFillColor(sf::Color::White);
		enemyView.push_back(rect);
	}



	sf::Texture* backgroundTexture = new sf::Texture;
	backgroundTexture->loadFromFile("./recources/TEXTURES/Background.png");

	backgroundSprite.setPosition(0, -20);
	backgroundSprite.setFillColor(sf::Color::White);
	backgroundSprite.setSize(sf::Vector2f(xRes, yRes));
	backgroundSprite.setTexture(backgroundTexture);
	
	grid.reset();
	grid.setupGrid();

	for (int i = 0; i < grid.TotalCells; i++)
	{
		grid.at(i)->weight = 1;
		grid.at(i)->m_isPassable = true;
	}

	texture[0].loadFromFile("./recources/TEXTURES/Texture.png");
	texture[1].loadFromFile("./recources/TEXTURES/Texture2.png");
	texture[2].loadFromFile("./recources/TEXTURES/brks_1.png");
	texture[3].loadFromFile("./recources/TEXTURES/brks_2.png");
	texture[4].loadFromFile("./recources/TEXTURES/Door.png");
	texture[5].loadFromFile("./recources/TEXTURES/tree.png");
	texture[6].loadFromFile("./recources/TEXTURES/Enemys/EnemyOne.png");
	texture[7].loadFromFile("./recources/TEXTURES/crate.png");
	texture[8].loadFromFile("./recources/TEXTURES/pints.png");
	texture[9].loadFromFile("./recources/TEXTURES/Medkit.png");
	

	texturesForEditor[0].loadFromFile("./recources/TEXTURES/Texture.png");
	texturesForEditor[1].loadFromFile("./recources/TEXTURES/Texture2.png");
	texturesForEditor[2].loadFromFile("./recources/TEXTURES/brks_1.png");
	texturesForEditor[3].loadFromFile("./recources/TEXTURES/brks_2.png");

	for (int i = 4; i < 12; i++) 
	{
		std::string url = "./recources/TEXTURES/Numbers/" + std::to_string(i + 1) +".png";
		texturesForEditor[i].loadFromFile(url);
	}

	int count = 0;

	for (int vec : m_level.m_blockType.at(currentLevel - 1).block)
	{
		//Load cobble texture
		if (vec == 1)
		{
			int cellID = grid.at(count)->getID();
			sf::Vector2f rectPos = grid.at(cellID)->cellBody.getPosition();
			//grid.at(cellID)->cellBody.setFillColor(sf::Color::Red);
			grid.at(cellID)->m_isPassable = false;
			grid.at(cellID)->weight = 9999999;

			Cube* cube = new Cube{ rectPos, 0 };
			cubes.push_back(cube);
		}
		else
		//Load Red brick texture old
		if (vec == 2)
		{
			int cellID = grid.at(count)->getID();
			sf::Vector2f rectPos = grid.at(cellID)->cellBody.getPosition();
			//grid.at(cellID)->cellBody.setFillColor(sf::Color::Red);
			grid.at(cellID)->m_isPassable = false;
			grid.at(cellID)->weight = 9999999;

			Cube* cube = new Cube{ rectPos, 1 };
			cubes.push_back(cube);
		}
		else
		//Load Red brick texture
		if (vec == 3)
		{
			int cellID = grid.at(count)->getID();
			sf::Vector2f rectPos = grid.at(cellID)->cellBody.getPosition();
			//grid.at(cellID)->cellBody.setFillColor(sf::Color::Red);
			grid.at(cellID)->m_isPassable = false;
			grid.at(cellID)->weight = 9999999;

			Cube* cube = new Cube{ rectPos, 2 };
			cubes.push_back(cube);
		}
		else
		//Load white brick texture
		if (vec == 4)
		{
			int cellID = grid.at(count)->getID();
			sf::Vector2f rectPos = grid.at(cellID)->cellBody.getPosition();
			//grid.at(cellID)->cellBody.setFillColor(sf::Color::Red);
			grid.at(cellID)->m_isPassable = false;
			grid.at(cellID)->weight = 9999999;

			Cube* cube = new Cube{ rectPos, 3 };
			cubes.push_back(cube);
		}
		else
		//Load billboard trees
		if (vec == 5)
		{
			int cellID = grid.at(count)->getID();
			sf::Vector2f rectPos = grid.at(cellID)->center;
			//grid.at(cellID)->cellBody.setFillColor(sf::Color::Green);
			grid.at(cellID)->weight = 3;

			BillboardedBoundary* bbound = new BillboardedBoundary{ rectPos, 5 ,16 };
			sprites.push_back(bbound);
		}
		else
		//Load Enemy type One
		if (vec == 6)
		{
			int cellID = grid.at(count)->getID();
			sf::Vector2f rectPos = grid.at(cellID)->center;

			EnemyOne* firstEnemy = new EnemyOne(rectPos);
			enemyTypeOne.push_back(firstEnemy);
		}
		else
		//Load pickup ammo
		if (vec == 7)
		{
			int cellID = grid.at(count)->getID();
			sf::Vector2f rectPos = grid.at(cellID)->center;

			pickupWeapon* pickup = new pickupWeapon{ rectPos, pickupType::Ammo };
			pickups.push_back(pickup);
			sprites.push_back(pickup->spriteBound);
		}
		else
		//Load pickup Health
		if (vec == 8)
		{
			int cellID = grid.at(count)->getID();
			sf::Vector2f rectPos = grid.at(cellID)->center;

			pickupWeapon* pickup = new pickupWeapon{ rectPos, pickupType::Health };
			pickups.push_back(pickup);
			sprites.push_back(pickup->spriteBound);
		}
		else
		//Load pickup pint
		if (vec == 9)
		{
			int cellID = grid.at(count)->getID();
			sf::Vector2f rectPos = grid.at(cellID)->center;

			pickupWeapon* pickup = new pickupWeapon{ rectPos, pickupType::Pint };
			pickups.push_back(pickup);
			sprites.push_back(pickup->spriteBound);
		}
		else
		//Load Vetical End Door
		if (vec == 10)
		{
			int cellID = grid.at(count)->getID();
			sf::Vector2f rectPos = grid.at(cellID)->center;

			sf::Vector2f pos1 = rectPos;
			pos1.y -= (grid.at(count)->cellBody.getGlobalBounds().height / 2);

			sf::Vector2f pos2 = rectPos;
			pos2.y += (grid.at(count)->cellBody.getGlobalBounds().height / 2);

			firstDoor = new Door{ pos1, pos2 , 4 };

			walls.emplace_back(firstDoor);
		}
		else
		//Load Horizontal End Door
		if (vec == 11)
		{
			int cellID = grid.at(count)->getID();
			sf::Vector2f rectPos = grid.at(cellID)->center;

			sf::Vector2f pos1 = rectPos;
			pos1.x -= (grid.at(count)->cellBody.getGlobalBounds().width / 2);

			sf::Vector2f pos2 = rectPos;
			pos2.x += (grid.at(count)->cellBody.getGlobalBounds().width / 2);

			firstDoor = new Door{ pos1, pos2 , 4 };

			walls.emplace_back(firstDoor);
		}
		else
		//Load Player
		if (vec == 12)
		{
			int cellID = grid.at(count)->getID();
			sf::Vector2f rectPos = grid.at(cellID)->center;

			player.refillAmmo();
			player.setPosition(rectPos);
		}

		count++;
	}

	for (auto& cube : cubes)
	{
		for (int i = 0; i < 4; i++)
		{
			walls.push_back(&cube->sides[i]); //UNPACKS CUBE OBJECT AND PUSHES ITS WALLS TO THE WALLS VECTOR, THIS MEANS WE DO NOT HAVE TO HAVE A SEPARATE CUBE CONTAINER PASSED TO THE PLAYER
		}
	}

	for (int index = 0; index < 400; index++)
	{
		grid.findNeigbours(grid.at(index)->x, grid.at(index)->y);
	}

	for (auto& enemy : enemyTypeOne)
	{
		enemy->setupPath(grid.at(grid.getCellPlayerIsIn(player.getPosition())), &grid);
	}
}

void Game::SyncData(LevelData t_data)
{
	isCustomMapInPlay = true;

	currentLevel = 1;

	if (m_level.m_blockType.size() > 0) 
	{
		m_level.m_blockType.at(0).block.clear();
	}

	for (int vec : t_data.m_blockType.at(0).block)
	{
		if (m_level.m_blockType.size() > 0)
		{
			m_level.m_blockType.at(0).block.push_back(vec);
		}
		else 
		{
			mapBlock block;

			m_level.m_blockType.push_back(block);

			m_level.m_blockType.at(0).block.push_back(vec);
		}
	}

	loadLevel(true);
}


void Game::drawDebug()
{
	castWindow.draw(debugText);
}

void Game::update(sf::Time timePerFrame)
{
	grid.update();

	switch (currentState)
	{
	default:
		break;
	case GameState::Game:
		
		

		checkBulletHit();

		player.movePlayer();

		player.update(&grid);
		
		for (auto& enemys : enemyTypeOne)
		{
			enemys->updatePos(&grid, player.oldCell, player.getPosition());
			enemys->sprite.updatePos(enemys->topViewRect.getPosition(), 16);
			enemys->sprite.updateV3(player.getPosition());
			enemys->checkForPlayerHit(grid.GetIntersects(player.getPosition()), player.health, timePerFrame.asSeconds());
		}

		for (auto& cube : cubes)
		{
			cube->checkCollisionsWithPlayer(player);
		}

		

		////TODO NEED TO CREATE A CONTAINER FOR PICKUPS AND LOOP THROUGH HERE
		for (auto& p : pickups)
		{
			p->spriteBound;
			if (pickupHandler::checkCollisions(player, *p))
			{
				sprites.erase(std::remove(sprites.begin(), sprites.end(), p->spriteBound), sprites.end());
				pickups.erase(std::remove(pickups.begin(), pickups.end(), p), pickups.end());
			}
			
		}

		if (thor::length(firstDoor->startPoint - player.getPosition()) <= firstDoor->detectionlength)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			{
				if (!isCustomMapInPlay)
				{
					if (currentLevel < MaxLevels) 
					{
						firstDoor->interact();
						currentLevel++;
						loadLevel(false);
					}
					else {
						currentLevel = 1;
						m_level.m_blockType.clear();
						loadLevel(false);
						currentState = GameState::MainMenu;
					}
				}
				else
				{
					currentState = GameState::MainMenu;
					m_level.m_blockType.clear();
					currentLevel = 1;
					loadLevel(false);
					isCustomMapInPlay = false;
				}
			}
		}

		break;
	case GameState::Endgame:
		m_window.close();
		break;
	case GameState::ResetGame:
		currentState = GameState::Game;
		currentLevel = 1;
		m_level.m_blockType.clear();
		loadLevel(false);
		break;
	case GameState::CustomMapGame:
		SyncData(editor.t_lev);
		currentState = GameState::Game;
		break;
	}
}

void Game::drawAndTextureWalls(int i)
{
	if (player.getrays()[i]->intersectionPoint != sf::Vector2f(INFINITY, INFINITY) && renderWalls)
	{
		float distBetween = thor::length(sf::Vector2f(player.getrays()[i]->intersectionPoint) - player.getrays()[i]->source);
		//	view[i].setFillColor(sf::Color::White - sf::Color(distBetween / 10, distBetween / 10, distBetween / 10));
		view[i]->setScale(sf::Vector2f(1, 100 / distBetween)); // this value seems kind of arbitrary, its to create the effect of z depth by drawing rects smaller when they are further out;

		int step = 32; //this should return the width of the texture in pixels, essentially getting the line between start and end of barrier. this step may not be necessary but it's in here

		sf::Vector2f test1 = player.getrays()[i]->intersectionPoint;
		sf::Vector2f test2 = player.getrays()[i]->getWall()->startPoint;

		Boundary* test3 = player.getrays()[i]->getWall();

		step -= thor::length((player.getrays()[i]->intersectionPoint) - player.getrays()[i]->getWall()->startPoint); // this will give a value from 0-32 depending on which pixel of the above line was hit by the ray, giving us the Y coord of the texture "slice", 
		 //there is probably a better method of determining which slice to draw that would produce cleaner results but I haven't figured it out yet

		if (distanceTransparencyEnabled)
		{
			view[i]->setFillColor(sf::Color::White - sf::Color(0, 0, 0, clamp(distBetween / 2, 0, 255)));
		}
		else
		{
			view[i]->setFillColor(sf::Color::White);
		}
		if (applyTextureToWall == true)
		{
			view[i]->setTexture(&texture[player.getrays()[i]->textureToRender]); // ray will pull an integer value from the barrier it collides with, and here we associate it with a texture thats already loaded within the game class.
			view[i]->setTextureRect(sf::IntRect(step % 32, 0, 0.2, 32)); //basic idea is to break the texture into vertical slices and apply them to the view rects, what slice it is is determined by distance from the boundary origin
		}
		//as of right now, the texture data is just the same thing for everything, but we can associate the texture data with the boundary class, giving each boundary its own color + texture;


		castWindow.draw(*view[i]);
	}
}

void Game::drawAndTextureSprites(int i)
{
	if (player.getrays()[i]->hitSprite && thor::length(sf::Vector2f(player.getrays()[i]->intersectionPoint) - player.getrays()[i]->source) > thor::length(sf::Vector2f(player.getrays()[i]->spriteHitDistance) - player.getrays()[i]->source) && renderSprites)
	{
		if (player.getrays()[i]->getSprite() != nullptr)
		{
			float distBetween = thor::length(sf::Vector2f(player.getrays()[i]->spriteHitDistance) - player.getrays()[i]->source);

			//	view[i].setFillColor(sf::Color::White - sf::Color(distBetween / 10, distBetween / 10, distBetween / 10));

			spritesView[i]->setScale(sf::Vector2f(1, 100 / distBetween)); // this value seems kind of arbitrary, its to create the effect of z depth by drawing rects smaller when they are further out;



			int step = 32; //this should return the width of the texture in pixels, essentially getting the line between start and end of barrier. this step may not be necessary but it's in here

			step -= thor::length((player.getrays()[i]->spriteHitDistance) - player.getrays()[i]->getSprite()->startPoint); // this will give a value from 0-32 depending on which pixel of the above line was hit by the ray, giving us the Y coord of the texture "slice", 
			 //there is probably a better method of determining which slice to draw that would produce cleaner results but I haven't figured it out yet



			if (applyTextureToSprite == true)
			{
				
				spritesView[i]->setTexture(&texture[player.getrays()[i]->spriteToRender]); // ray will pull an integer value from the barrier it collides with, and here we associate it with a texture thats already loaded within the game class.
				spritesView[i]->setTextureRect(sf::IntRect(step % 32, 0, 0.2, 32)); //basic idea is to break the texture into vertical slices and apply them to the view rects, what slice it is is determined by distance from the boundary origin
				//as of right now, the texture data is just the same thing for everything, but we can associate the texture data with the boundary class, giving each boundary its own color + texture, since the width is 0.2, the texture can repeat up to 5 times based on
				//the distance between the adjacent intersection points.
			}

			if (distanceTransparencyEnabled)
			{
				spritesView[i]->setFillColor(sf::Color::White - sf::Color(0, 0, 0, clamp(distBetween / 2, 0, 255)));
			}
			else
			{
				spritesView[i]->setFillColor(sf::Color::White);
			}
			castWindow.draw(*spritesView[i]);
		}
	}
}

void Game::drawAndTextureEnemies(int i)
{
	if (player.getrays()[i]->hitEnemy && thor::length(sf::Vector2f(player.getrays()[i]->intersectionPoint) - player.getrays()[i]->source) > thor::length(sf::Vector2f(player.getrays()[i]->enemyHitDistance) - player.getrays()[i]->source))
	{
		if (player.getrays()[i]->getEnemy() != nullptr)
		{
			float distBetween = thor::length(sf::Vector2f(player.getrays()[i]->enemyHitDistance) - player.getrays()[i]->source);

			//	view[i].setFillColor(sf::Color::White - sf::Color(distBetween / 10, distBetween / 10, distBetween / 10));

			enemyView[i]->setScale(sf::Vector2f(1, 100 / distBetween)); // this value seems kind of arbitrary, its to create the effect of z depth by drawing rects smaller when they are further out;

			int step = 32; //this should return the width of the texture in pixels, essentially getting the line between start and end of barrier. this step may not be necessary but it's in here

			step -= thor::length((player.getrays()[i]->enemyHitDistance) - player.getrays()[i]->getEnemy()->getSprite()->startPoint); // this will give a value from 0-32 depending on which pixel of the above line was hit by the ray, giving us the Y coord of the texture "slice", 
			 //there is probably a better method of determining which slice to draw that would produce cleaner results but I haven't figured it out yet

			enemyView[i]->setTexture(&texture[player.getrays()[i]->enemyToRender]); // ray will pull an integer value from the barrier it collides with, and here we associate it with a texture thats already loaded within the game class.

			enemyView[i]->setTextureRect(sf::IntRect(step % 32, 0, 0.2, 32)); //basic idea is to break the texture into vertical slices and apply them to the view rects, what slice it is is determined by distance from the boundary origin

			enemyView[i]->setFillColor(sf::Color::White - sf::Color(0, 0, 0, clamp(distBetween / 2, 0, 255)));

			castWindow.draw(*enemyView[i]);
		}
	}
}

void Game::render()
{
	m_window.clear();

	//if in VS Debug mode render grid
	#ifdef _DEBUG 
		grid.draw(m_window);
	#endif

	player.draw(m_window, walls,sprites, spritesView, enemyTypeOne);

	for (Boundary* wls : walls)
	{
		wls->draw(m_window);
	}

	for (BillboardedBoundary* bb : sprites)
	{
		bb->draw(m_window);
	}

	for (EnemyOne* enemy : enemyTypeOne)
	{
		enemy->sprite.draw(m_window);
		m_window.draw(enemy->topViewRect);
	}

	ImGui::SFML::Update(m_window, deltaClock.restart());
	ImGui::Begin("Debug Menu");
	ImGui::Text("Texture bools");
	ImGui::Checkbox("Texture Walls?", &applyTextureToWall);
	ImGui::Checkbox("Texture Sprites?", &applyTextureToSprite);
	ImGui::Text("Fog effects");
	ImGui::Checkbox("Distant fog sprite?", &drawBackgroundSprite);
	ImGui::Checkbox("Wall Distance Transparency", &distanceTransparencyEnabled);
	ImGui::Text("Object Rendering");
	ImGui::Checkbox("Render walls", &renderWalls);
	ImGui::Checkbox("Render sprites", &renderSprites);
	ImGui::Text("AI Debugging");
	ImGui::Checkbox("Render path", &renderPath);


	ImGui::End();
	ImGui::SFML::Render(m_window);

	if (renderPath)
	{
		for (auto e : enemyTypeOne)
		{
			e->updateLines(m_window, &grid);
		}
	}

	m_window.display();
	
	castWindow.clear();

	switch (currentState)
	{
	default:
		break;
	case GameState::SplashScreen:
		ss.render(castWindow);
		break;
	case GameState::MainMenu:
		mm.render(castWindow);
		break;
	case GameState::Game:
		drawGame();
		break;
	case GameState::Death:
		ds.render(castWindow);
		break;
	case GameState::LevelEdit:
		editor.draw(castWindow);
		break;
	}
	
	
	castWindow.display();
}

void Game::checkBulletHit()
{
	for (auto& e : enemyTypeOne)
	{
		for (int j = 0; j < player.MAXAMMOPERMAG; j++)
		{
			if (player.bullets[j].bulletState == Bullet::State::moving)
			{
				if (player.bullets[j].bulletBody.getGlobalBounds().intersects(e->topViewRect.getGlobalBounds()) &&
					e->alive)
				{
					e->takeDamage();
					enemyTypeOne.erase(std::remove(enemyTypeOne.begin(), enemyTypeOne.end(), e), enemyTypeOne.end());


				}
			}
		}
	}
}

float Game::clamp(float n, float lower, float upper) {
	return std::max(lower, std::min(n, upper));
}
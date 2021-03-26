#include "Game.h"


Game::Game()
	: m_window{ sf::VideoMode{1920, 1080}, "SMFL Game",  } 
{

	setupLevel(5);

	
}

void Game::setupLevel(int t_amountZombies)
{

	//clears vector of zombies to avoid leaks when recreating levels;
	
	for (auto z : zombie)
	{
		delete z;
	}
	for (auto w : basicWall)
	{
		delete w;
	}
	zombie.clear();

	amountZombies = t_amountZombies;

	consumable[0] = new Medkit(0.5, "medkit.png", sf::Vector2f(1200, 600));
	consumable[1] = new Ammocrate(0.15, "ammocrate.png", sf::Vector2f(110, 1200));

	for (int i = 0; i < 10; i++)
	{
		basicWall[i] = new Wall(sf::Vector2f(0, 0), 10, 10);

	}

	basicWall[0] = new Wall(sf::Vector2f(0, 0), 10, 2050);

	basicWall[0]->body.setPosition(0, 1025);


	basicWall[1] = new Wall(sf::Vector2f(0, 0), 10, 2050);

	basicWall[1]->body.setPosition(2050, 1025);

	basicWall[2] = new Wall(sf::Vector2f(0, 0), 2050, 10);

	basicWall[2]->body.setPosition(1025, 0);


	basicWall[3] = new Wall(sf::Vector2f(0, 0), 2050, 10);

	basicWall[3]->body.setPosition(1025, 2050);


	
	basicWall[4] = new Wall(sf::Vector2f(0, 0), 2050, 10);

	basicWall[4]->body.setPosition(800, 800);

	m_window.setFramerateLimit(144);
	m_window.setMouseCursorVisible(false);
	player.initialise();

	view.reset(sf::FloatRect(0, 0, 1920, 1080));

	view.setViewport(sf::FloatRect(0, 0, 1.0f, 1.0f));

	view.setCenter(player.getPosition());

	if (!backgroundtexture.loadFromFile("ART/background.png"))
	{
		//error;
	}
	background.setTexture(backgroundtexture);
	background.setScale(2, 2);
	background.setPosition(0, 0);
	player.setPosition(sf::Vector2f(0, 0));
	view.setCenter(player.getPosition());

	for (int i = 0; i < amountZombies; i++)
	{

		zombie.push_back(new Zombie);
		zombie[i]->init();
	}
	zombie[0]->setPosition(zombie[0]->getPosition() + sf::Vector2f(0, 20));




	m_window.setMouseCursorGrabbed(false);
	weather.init();

	player.setPosition(sf::Vector2f(1000, 500));

	for (int i = 0; i < 10; i++)
	{
		basicWall[i]->lastKnownPlayerPos = player.getPosition();
	}


}

	

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	sf::Time timePerFrame = sf::seconds(1.f / 60.f);
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

void Game::processCollisions()
{
	for (auto z: zombie)
	{
	

		for (int j = 0; j < 30; j++)
		{
			if (player.bullet[j].bulletState == Bullet::State::moving)
			{
				if (player.bullet[j].bulletBody.getGlobalBounds().intersects(z->collisionBox.getGlobalBounds()) &&
					z->alive)
				{
					z->alive = false;
					
					currentZombies--;
					
					
				
				}
			}
		}






		if (z->zombieProjectile.bulletState == Bullet::State::moving)
		{
			if (z->zombieProjectile.bulletBody.getGlobalBounds().intersects(player.collisionBox.getGlobalBounds()))
			{
				player.currentLives -= 1;
				player.currentStamina -= 10;
				z->stopProjectile();
			}
		}
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();

		}
		
	}
}

void Game::update(sf::Time)
{
	for (auto z: zombie)

	{
		for (int j = 0; j < 5; j++)
		{
			z->updateLineToPlayer(player.getPosition(), basicWall[j]->body);
		}
	}



	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::C))
	{
		Game::setupLevel(5);
	}



	checkGameOver();
	processCollisions();
	checkPickup();
	player.processInput();
	player.update(m_window);
	player.updateUI(view);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		m_window.close();
	}
	

	//10 walls for collision
	for (int j = 0; j < 10; j++)
	{
		basicWall[j]->checkCollisionsWithPlayer(player);
	for (int i = 0; i < amountZombies; i++)
	{

		
			
			basicWall[j]->checkCollisionsWithEnemy(*zombie[i]);
		}
	}
	weather.update(m_window);
}

void Game::render()
{
	view.setRotation(0);
	
	
	
	
	

	//	if (player.getPosition().x - 500 > 0 && player.getPosition().x + 500 < 1920 )
		{
			view.setCenter(player.getPosition().x, view.getCenter().y);
		}

	//	if (player.getPosition().y > 0 && player.getPosition().y < 1752)
		{
			view.setCenter(view.getCenter().x, player.getPosition().y);
		}


		if (player.shooting)
		{
			//view.setRotation(rand() % 5);
			view.setCenter(sf::Vector2f(player.getPosition().x, view.getCenter().y) + sf::Vector2f(rand() % 15, rand() % 15));
		}


	m_window.clear();
	m_window.draw(background);
	for (int i = 0; i < 2; i++)
	{
		consumable[i]->draw(m_window);
	}
	
	for (int i = 0; i < amountZombies; i++)
	{
		zombie[i]->update(player.getPosition(), player.detectRadius.getRadius(), player.collisionBox);
	}
	m_window.setView(view);
	player.draw(m_window);
	for (int i = 0; i < amountZombies; i++)
	{
		zombie[i]->draw(m_window);
	}
	weather.draw(m_window);


	for (int i = 0; i < 10; i++)
	{
		basicWall[i]->draw(m_window);
	}
	m_window.display();
	
}

void Game::checkPickup()
{
	if (player.playerSprite.getGlobalBounds().intersects(((Medkit*)consumable[0])->consumableSprite.getGlobalBounds() )
		&& ((Medkit*)consumable[0])->active == true && player.currentLives < player.MAXLIVES)
	{
		((Medkit*)consumable[0])->pickup(player);
		
		
	}

	if (player.playerSprite.getGlobalBounds().intersects(((Ammocrate*)consumable[1])->consumableSprite.getGlobalBounds())
		&& ((Ammocrate*)consumable[1])->active == true )
	{
		((Ammocrate*)consumable[1])->pickup(player);
		
	}
}

void Game::checkGameOver()
{
	if (player.currentStamina <= 0)
	{
		m_window.close();
	}


	if (currentZombies <= 0)
	{
		m_window.close();
	}
}



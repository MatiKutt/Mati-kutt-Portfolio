//Mati Kutt
//https://instituteoftechnol663-my.sharepoint.com/:v:/g/personal/c00250720_itcarlow_ie/ET7MfdaXqgBPsPlBpAkTy1oBANNCEDhLj3D4wRxUZSLTHQ?email=Noel.OHara%40itcarlow.ie&e=8TzVXg
#pragma once
#include "SFML/Graphics.hpp"
#include "Animation.h"
#include "Coin.h"


class Game
{
public:
	//create Window
	AnimationSheet robotAnimationSheet;
	Animation robotAnimationRun;
	Animation robotAnimationFall;

	Animation coinAnimation;
	AnimationSheet coinAnimationSheet;


	Coin coin[50];
	int amountCoins{ 0 };
	Animation robotAnimationJump;

	AnimationSheet robotAnimationJumpingSheet;
	AnimationSheet robotAnimationFallingSheet;
	sf::Texture playerTexture;
	sf::Sprite playerSprite;
	int points{ 0 };
	sf::Text pointsText;
	sf::Font UIFont;

	sf::RenderWindow window;
	sf::View view;
	float randomNum;
	float timeChange = 0;

	sf::RectangleShape playerShape;
	int pixelsPerMeter = 80;

	sf::Vector2f velocity{ 0,0 };
	sf::Vector2f gravity{ 0,12};
	sf::Vector2f jumpPushOff{ 0,6 * pixelsPerMeter };



	static const int numRows = 45;
	static const int numCols = 20;
	int levelData[numRows][numCols] =
	{
	{ 1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,1,0,2,2 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,2,1 },
	{ 0,0,0,0,0,0,0,0,0,0,5,0,0,2,2,1,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,3,0,0,1,0,0,0,0,0,1 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0 },
	{ 0,5,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,1,0,0,0,0,1,1,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,5,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0 },
	{ 0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,1,1,1,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,5,1,0,0,0,0,1,1,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,0,0 },
	{ 0,0,0,1,1,1,0,0,0,0,0,0,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,1,1,1,1,1,0,1,0,0,0,0,0,0 },
	{ 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 },
	{ 0,0,0,0,4,4,4,0,0,0,0,0,0,0,0,0,0,0,0,0 } };

	sf::RectangleShape level[numRows][numCols];

	Game()
	{  
		Coin testCoin;
		testCoin.init(sf::Vector2f(0,0));

		window.create(sf::VideoMode(800, 600), "Endless Runner Game");
		playerTexture.loadFromFile("walkingrobot.png");
		playerSprite.setTexture(playerTexture);
		
		
		UIFont.loadFromFile("font.ttf");
		pointsText.setFont(UIFont);
		pointsText.setCharacterSize(24);
		pointsText.setFillColor(sf::Color::White);
		pointsText.setPosition(0, 0);
		pointsText.setOutlineColor(sf::Color::Black);
		pointsText.setOutlineThickness(1);

		playerSprite.setOrigin(96.0f/2 - 20,   128.0f/2 + 20);

		coinAnimation.startOffset = 1;
		coinAnimation.numframes = 5;
		coinAnimation.speed = 5;
		coinAnimation.loop = true;

		
		
		


		robotAnimationRun.startOffset = 0;
		robotAnimationRun.loop = true;
		robotAnimationRun.speed = 5;
		robotAnimationRun.numframes = 8;

		robotAnimationFall.loop = true;
		robotAnimationFall.numframes = 1;
		robotAnimationFall.speed = 1;
		robotAnimationFall.startOffset = 2;

		robotAnimationJump.loop = true;
		robotAnimationJump.numframes = 1;
		robotAnimationJump.speed = 1;
		robotAnimationJump.startOffset = 1;

		
		robotAnimationSheet.Init(playerSprite.getGlobalBounds().width, playerSprite.getGlobalBounds().height, 4, 9);
		robotAnimationFallingSheet.Init(playerSprite.getGlobalBounds().width, playerSprite.getGlobalBounds().height, 0, 9);
		robotAnimationJumpingSheet.Init(playerSprite.getGlobalBounds().width, playerSprite.getGlobalBounds().height, 0, 9);
		coinAnimationSheet.Init(testCoin.coinSprite.getGlobalBounds().width, testCoin.coinSprite.getGlobalBounds().height, 0, 5);



		robotAnimationFallingSheet.StartAnimation(robotAnimationFall);
		robotAnimationJumpingSheet.StartAnimation(robotAnimationJump);
		robotAnimationSheet.StartAnimation(robotAnimationRun);
		coinAnimationSheet.StartAnimation(coinAnimation);
	



		robotAnimationSheet.frameSize = sf::Vector2i(96, 128);
		robotAnimationFallingSheet.frameSize = sf::Vector2i(96, 128);
		robotAnimationJumpingSheet.frameSize = sf::Vector2i(96, 128);
		coinAnimationSheet.frameSize = sf::Vector2i(16, 16);

		playerSprite.setScale(.5, .5);
	}

	void jumpBlock()
	{
		
		velocity.y = (-jumpPushOff.y* 2) * timeChange;
	}

	void init()
	{
		amountCoins = 0;
		for (int i = 0; i < 50; i++)
		{
			coin[i].active = false;
		}
		

		points = 0;
		pointsText.setString("Points: " + points);
		

		view = window.getDefaultView();
		playerShape.setSize(sf::Vector2f(20, 20));
		playerShape.setPosition(160, 500);

		for (int row = 0; row < numRows; row++)
		{
			for (int col = 0; col < numCols; col++)
			{

				if (levelData[row][col] == 1)
				{

					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					int randNum{};
					randNum = rand() % 3 + 1;
					switch (randNum)
					{
					default:
						break;
					case 1:
						level[row][col].setFillColor(sf::Color(75, 47, 220));
						break;
					case 2:
						level[row][col].setFillColor(sf::Color(70, 47, 190));
						break;
					case 3:
						level[row][col].setFillColor(sf::Color(70, 47, 153));
						break;
					}
					
				}
				if (levelData[row][col] == 0)
				{

					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color(235 - (col * 3),235, 140));
				}
				if (levelData[row][col] == 2)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);

					level[row][col].setFillColor(sf::Color(255, 0, 0));

				}
				if (levelData[row][col] == 3)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);

					level[row][col].setFillColor(sf::Color::Green);

				}
				if (levelData[row][col] == 4)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);

					level[row][col].setFillColor(sf::Color::Magenta);

				}
				if (levelData[row][col] == 5)
				{
					level[row][col].setSize(sf::Vector2f(70, 30));
					level[row][col].setPosition(row * 70, col * 30);
					level[row][col].setFillColor(sf::Color(235 - (col * 3), 235, 140));
					coin[amountCoins].init(sf::Vector2f(row * 70, col * 30));
					amountCoins++;
				}
			}
			
		}

	}
	void run()
	{


		sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);


		sf::Time timeSinceLastUpdate = sf::Time::Zero;


		sf::Clock clock;

		clock.restart();

		while (window.isOpen())
		{

			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}


			timeSinceLastUpdate += clock.restart();


			if (timeSinceLastUpdate > timePerFrame)
			{
				timeChange = (float)timeSinceLastUpdate.asSeconds();
				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{

						level[row][col].move(-3.7, 0);
					}

				}


				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && velocity.y == 0)
				{
					velocity.y += -jumpPushOff.y * timeChange; 
					
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) == false )
				{
					velocity.y = velocity.y + gravity.y * timeChange;
				}

				velocity.y = velocity.y + gravity.y * timeChange;
				playerShape.move(0, velocity.y);


				gravity = sf::Vector2f(0,12);

				for (int row = 0; row < numRows; row++)
				{
 					for (int col = 0; col < numCols; col++)
					{
						if (velocity.y >= 0)
						{
							if (levelData[row][col] == 1)
							{

								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									if (playerShape.getPosition().y < level[row][col].getPosition().y)
									{
										gravity.y = 0;
										velocity.y = 0;
										playerShape.setPosition(playerShape.getPosition().x, level[row][col].getPosition().y);
										playerShape.move(0, -playerShape.getGlobalBounds().height);
										break;
									}
									else {
										init();
									}
								}


							}

						}
						if (velocity.y < 0)
						{
							if (levelData[row][col] == 1)
							{
								if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
								{
									init();
								}

							}

						}
						if (levelData[row][col] == 2)
						{
							if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
							{
								init();
							}
						}
						if (levelData[row][col] == 3)
						{
							if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
							{
								jumpBlock();
							}
						}
						if (levelData[row][col] == 4)
						{
							if (playerShape.getGlobalBounds().intersects(level[row][col].getGlobalBounds()))
							{
								window.close();
							}
						}
						if (levelData[row][col] == 5)
						{
							
						}
					}
				}

				if (playerShape.getPosition().y > 600)
				{
					init();
				}



				window.clear(sf::Color(235, 235, 140));



				for (int row = 0; row < numRows; row++)
				{
					for (int col = 0; col < numCols; col++)
					{
						window.draw(level[row][col]);

					}
				}


				


				robotAnimationSheet.nextFrame();
				robotAnimationFallingSheet.nextFrame();
				coinAnimationSheet.nextFrame();


				playerSprite.setPosition(playerShape.getPosition());
			



				//animate player
				if (velocity.y == 0)
				{

					//robotAnimationSheet.StartAnimation(robotAnimationRun);
					playerSprite.setTextureRect(robotAnimationSheet.GetFrame());
				}
				else if (velocity.y > 0) //if falling
				{
					playerSprite.setTextureRect(robotAnimationFallingSheet.GetFrame());
				}
				else if (velocity.y < 0) // if jumping
				{
					playerSprite.setTextureRect(robotAnimationJumpingSheet.GetFrame());
				}


				window.draw(playerSprite);
				window.draw(pointsText);
				for (int i = 0; i < amountCoins; i++)
				{
					
					coin[i].coinBody.move(-3.7, 0);
					coin[i].coinSprite.setPosition(coin[i].coinBody.getPosition());
					

					if (playerShape.getGlobalBounds().intersects(coin[i].coinBody.getGlobalBounds()) && coin[i].active)
					{
						coin[i].active = false;
						points++;
						pointsText.setString("Points: " + std::to_string(points));
					}
					if (coin[i].active)
					{
						coin[i].coinSprite.setTextureRect(coinAnimationSheet.GetFrame());
						coin[i].draw(window);
						
						
					}
				}
				

		       // window.draw(playerShape);

				
			   

				
				
				window.display();

				timeSinceLastUpdate = sf::Time::Zero;
			}
		}
	}
};
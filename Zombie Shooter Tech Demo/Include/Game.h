#ifndef GAME
#define GAME

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "VectorAlgebra2D.h"
#include "Medkit.h"
#include "Ammocrate.h"
#include "Weather.h"
#include "Zombie.h"
#include "Wall.h"
#include "Thor/Graphics.hpp"



class Game
{
public:
	Game();
	void run();
	int amountZombies = 5;
	Player player;
	
	std::vector<Zombie*> zombie;
	Consumable *consumable[2];
	Wall* basicWall[10];
	int currentZombies = amountZombies;

private:
	void			 setupLevel(int t_amountZombies);
	void			 processCollisions();
	void             processEvents();
	void             update(sf::Time);
	void             render();
	void             checkPickup();
	void			 checkGameOver();
	sf::Vector2f     viewMove{ 0,0 };
	sf::Sprite       background;
	sf::Texture      backgroundtexture;
	Weather          weather;
private:
	
	sf::RenderWindow m_window;
	sf::View view;
};

#endif // !GAME

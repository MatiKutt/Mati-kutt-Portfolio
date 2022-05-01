#pragma once
#include <SFML/Graphics.hpp>
#include <Thor/Input.hpp>
#include <Thor/Vectors.hpp>
#include "Ray.h"
#include "Boundary.h"
#include "GLOBALS.h"
#include "bullet.h"
#include "BillboardedBoundary.h"
#include "EnemyOne.h"
#include <SFML/Audio.hpp>
//#include "pickupWeapon.h"
class Player
{
public:
	Player();
	~Player();
	void movePlayer();
	void update(Grid* grid);
	void processFireInput();
	sf::Vector2f getPosition();
	void setPosition(sf::Vector2f t_newPos);
	bool canMove = true;
	void draw(sf::RenderWindow& t_window, std::vector<Boundary*> walls, std::vector<BillboardedBoundary*> sprites, std::vector<sf::RectangleShape*> spritePlane, std::vector<EnemyOne*> enemys);
	std::vector<Ray*> getrays();
	void reload();
	void refillAmmo();
	int getAmmo();
	sf::Texture flashTexture;
	sf::Sprite flashSprite;
	sf::RectangleShape collisionBox;
	bool				shooting = false;
	bool flashOn = false;

	int					rateOfFireLimit = 0;
	const int			ROFTIMEOUTCAP = 6;
	void addPints();
	void addHealth();
	int getPints();
	int getHealth();
	static const int MAXAMMOPERMAG = 256;
	Cell* oldCell = nullptr;
	Bullet bullets[MAXAMMOPERMAG];
	int health = 7;

private:
	int pints =0;
	int					ammoInMag = 60;
	int					ammoInReserve = 20;
	int					reloadTimer = 120;
	bool				reloading = false;


	sf::SoundBuffer gunShotBuffer;
	sf::Sound gunShot;

	//void pickupItem(pickupType t_type);

	
	
	void setupPlayer();
	sf::Vector2f playerPos;
	std::vector<Ray*> rays;
};


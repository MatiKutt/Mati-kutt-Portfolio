#ifndef GAME
#define GAME

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Boundary.h"
#include "Player.h"
#include <vector>
#include "GLOBALS.h"
#include "UI.h"
#include "Grid.h"
#include "MainMenu.h"
#include "SplashScreen.h"
#include "Door.h"
#include "BillboardedBoundary.h"
#include "Cube.h"
#include <math.h>
#include "EnemyOne.h"
#include "LevelLoader.h"
#include "pickupWeapon.h"
#include "pickupHandler.h"
#include "DeathScreen.h"
#include "LevelEditor.h"


enum class GameState
{
	SplashScreen,
	MainMenu,
	Game,
	CustomMapGame,
	LevelEdit,
	MiniMap,
	Death,
	ResetGame,
	Endgame
};


class Game
{
public:
	Game();
	float clamp(float n, float lower, float upper);
	void run();
	void update(sf::Time timePerFrame);
	sf::RectangleShape backgroundSprite, ceiling;
	std::vector<Boundary*> walls;
	std::vector<BillboardedBoundary*> sprites;
	std::vector<Cube*> cubes;
	std::vector<pickupWeapon*> pickups;
	std::vector<sf::RectangleShape*> view;
	std::vector<sf::RectangleShape*> spritesView;
	std::vector<sf::RectangleShape*> enemyView;
	Player player;
	sf::Texture texture[10];
	UI playerUI;
	Grid grid;
	Door* firstDoor;
	static GameState currentState;
	LevelData m_level;
	DeathScreen ds;
	void loadLevel(bool isCustomMap);
	void SyncData(LevelData t_data);
	bool isCustomMapInPlay = false;
	sf::Texture texturesForEditor[12];

private:
	void drawAndTextureWalls(int i);
	void drawAndTextureSprites(int i);
	void drawAndTextureEnemies(int i);
	void render();
	void checkBulletHit();
	void processEvents();


	sf::SoundBuffer mainMusicBuffer;
	sf::Sound mainMusic;

	LevelEditor editor;
	sf::RenderWindow m_window;
	sf::RenderWindow castWindow;
	void drawGame();
	void drawDebug();
	sf::Text debugText;
	bool debug = false;
	bool applyTextureToWall = true;
	bool applyTextureToSprite = true;
	bool drawBackgroundSprite = true;
	bool distanceTransparencyEnabled = true;
	bool renderWalls = true;
	bool renderEnemy = true;
	bool renderSprites = true;
	bool renderPath = true;
	sf::Clock deltaClock;
	SplashScreen ss;
	MainMenu mm;
	sf::Font font;
	std::vector<EnemyOne*> enemyTypeOne;
	int currentLevel = 1;
	int MaxLevels = 3;
};


#endif // !GAME
#pragma once
#include <SFML/Graphics.hpp>
#include "VectorAlgebra2D.h"
#include <iostream>
#include "MathUtility.h"
#include <Thor/Shapes.hpp>
#include <Thor/Shapes/Arrow.hpp>
#include <Bullet.h>
class Zombie
{
	
public:
	

	sf::Clock idleTimer;
	sf::Clock firingCooldown;
	void stopProjectile();

	bool finishedAttacking = true;
	enum class State{Idle, patrolling, following, attacking};
	State currentState = State::Idle;


	bool alive = true;


	float areaOrig;
	float area1;
	float area2;
	float area3;

	// Vision cone vector...initially points along the x axis.
	sf::Vector2f m_visionConeDir{ 1, 0 };

	// Vision cone visualisation...vision cone origin
	sf::Vector2f m_visionConeLeft;

	sf::Vector2f m_visionConeRight;

	Bullet zombieProjectile;
	
	
	thor::Arrow m_arrowLeft;
	thor::Arrow m_arrowRight;
	static constexpr float VISION_CONE_LENGTH{ 400.0f };
	float baseConeRotation{ 0 };
	// visualisation cone end

	void updateVisionCone();
	void turnToPlayer(sf::Vector2f t_playerPos);
	void processFollowPlayer(sf::Vector2f t_playerPos);
	void processIdle(sf::Vector2f t_playerPos);
	void processAttacking();
	void updateCone(sf::RectangleShape t_playerCollisionBox);
	void updateLineToPlayer(sf::Vector2f t_playerPos, sf::RectangleShape t_wall);
	sf::RectangleShape lineToPlayer;
	bool lineInterrupted = false;

	int aggroTime = 0;
	int aggroMaxTime = 360;
	float speed = 0.5f;
	int attackFrameCountDown = 0;
	const int ATTACKANIMATESPEED = 12;
	sf::RectangleShape collisionBox;
	int currentMoveFrame = 0;
	int currentAttackFrame = 0;
	int animateSpeed = 8;
	int frameCountDown = 0;
	const int AMOUNTTEXTURES = 16;
	const int AMOUNTATTACKTEXTURES = 8;
	sf::Texture zombieIdleTexture[16];
	sf::Sprite zombieSprite;
	sf::Texture zombieAttackTexture[8];
	sf::Texture zombieMoveTexture[16];
	sf::Vector2f velocity{ };
	int AMOUNTFRAMES = 19;
	void init();
	void draw(sf::RenderWindow& t_window);
	void update(sf::Vector2f t_playerPos, int t_detectionRadius, sf::RectangleShape t_playerCollisionBox);
	void animate();
	void moveRandomly();
	void setPosition(sf::Vector2f t_pos);
	sf::Vector2f getPosition();
	sf::Vector2f lastKnownPlayerPos;
	sf::Vector2f randomGoalPosition;
};


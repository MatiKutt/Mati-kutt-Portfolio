#pragma once
#include <SFML/Graphics.hpp>
#include "VectorAlgebra2D.h"
#include "Bullet.h"
#include <iostream>
class Player
{
public:
	//sprite and texture variables
	sf::Texture         playerTexture[19];
	sf::Sprite          playerSprite;
	sf::Texture         shootingTexture[3];
	sf::Texture         reloadTexture[19];
	sf::Sprite			legsSprite;
	sf::Texture			legsTexture[19];
	sf::Texture			crosshairTexture;
	sf::Sprite			crosshairSprite;
	sf::Sprite			damageSprite;
	sf::Texture			damageTexture;
	sf::Texture			bloodTrailTexture;
	sf::Sprite			bloodTrailSprite[30];
	int amountBloodStainsOut = 0;


	//detection variables
	sf::Vector2f        detectOrigin{};
	const int           NOTMOVINGDETECTION = 30;
	const int           MOVINGDETECTION = 90;
	const int           SPRINTINGDETECTION = 120;
	sf::CircleShape     detectRadius;


	// animation variables
	float               BASEANIMATESPEED = 6;
	static const int    SHOOTSPRITEFRAMES = 3;
	//legs animation
	int					legsMoveFrame = 0;
	int					legsMoveFrameCounter = 0;
	//shoot animation
	int					shootFrame = 0;
	int					shootFrameChangeCounter = 0;
	int					shootAnimateSpeed = 1;
	//reload animation
	int					reloadFrameChangeCounter = 0;
	int					reloadFrame = 0;
	int					reloadAnimateSpeed=6.3;
	static const int	AMOUNTRELOADFRAMES = 19;
	//move animation
	int					moveFrame = 0;
	int					moveFrameChangeCounter = 0;
	float				animateSpeed = 6;
	static const int	AMOUNTFRAMES = 19;

	sf::Clock			bloodTrailTimer;

	sf::Vector2f		playerRotationAngle;// polar angle between mouse position and player position
	//UI element variables
	sf::Text            playerText;// text object for player speech 
	sf::Font            playerFont;// font for player text
	std::string         playerString;//string for player text
	sf::RectangleShape	stamBar;//stamina bar
	int					textTimeOut = 0;//text disappearing counter
	const int			MAXTEXTTIMEOUT = 120;//how long text stays active
	sf::Text			UItext; //UI debug text
	sf::Font			UIfont;// font for UI


	//*****Gameplay variables*****
	//shooting and reloading 
	bool				shooting = false;
	Bullet				bullet[30];
	int					rateOfFireLimit = 0;
	const int			MAXAMMOPERMAG = 30;
	int					ammoInMag = 30;
	int					ammoInReserve = 0;
	int					reloadTimer = 120;
	bool				reloading = false;
	const int			ROFTIMEOUTCAP = 6;
	//movement variables
	const float			playerSpeed = 2;
	const float			MAXSTAMINA = 120;
	float				currentStamina = MAXSTAMINA;
	bool				moving = false;
	sf::RectangleShape	collisionBox;
	
	
	const int			MAXLIVES = 3;
	int					currentLives = MAXLIVES;
	sf::Vector2f		mouseRelativeToWindowPos;
	

	
	


	//member functions
	sf::Vector2f		getPosition();
	void				heal();
	void				animate();
	void				updateText();
	void				animateLegsWalking();
	void				animateWalking();
	void				animateReload();
	void				animateShooting();
	void				resetShootingAnimation();
	void				setPosition(sf::Vector2f t_newPos);
	void				updateUI(sf::View t_view);
	void				initialise();
	void				draw(sf::RenderWindow& t_window);
	void				processInput();
	void				processSprintInput();
	void				processNormalMove();
	void				processFireInput();
	void				update(sf::RenderWindow &t_window);
	void				reload();
	void				refillAmmo();
	void				processDetectionRadius();
	
};


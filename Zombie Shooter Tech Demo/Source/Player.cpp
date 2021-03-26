#include "Player.h"


//returns position of player in world coordinates
sf::Vector2f Player::getPosition()
{
	return playerSprite.getPosition();
}

//adds a life to player
void Player::heal()
{
	currentLives++;
	currentStamina = MAXSTAMINA;
}

//method to handle what animations play
void Player::animate()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) == true && currentStamina > 0)
	{
		animateSpeed = BASEANIMATESPEED * 0.75;
	}
	else
	{
		animateSpeed = BASEANIMATESPEED;
	}


	






	if (moving && reloading == false && sf::Mouse::isButtonPressed(sf::Mouse::Left) == false)
	{
		animateWalking();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) == false && shootFrame!=0)
	{
		resetShootingAnimation();
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && reloading == false && ammoInMag > 0)
	{
		animateShooting();
	}

	else if (reloading)
	 {
		animateReload();
	 }
	
}

void Player::updateText()
{
	if (textTimeOut >= MAXTEXTTIMEOUT)
	{
		playerText.setString("");
		textTimeOut = 0;
	}
	if (playerText.getString() != "")
	{
		textTimeOut++;
	}

	playerText.setPosition(getPosition() - sf::Vector2f(playerText.getGlobalBounds().width / 2, 70));
}


//animates player legs when moving
void Player::animateLegsWalking()
{
	legsMoveFrameCounter++;

	if (legsMoveFrameCounter >= animateSpeed)
	{
		legsMoveFrameCounter = 0;
		legsSprite.setTexture(legsTexture[legsMoveFrame]);
		legsMoveFrame++;
		if (legsMoveFrame == AMOUNTFRAMES)
		{
			legsMoveFrame = 0;
		}


	}
}


//animates player torso when walking
void Player::animateWalking()
{
	moveFrameChangeCounter++;

	if (moveFrameChangeCounter >= animateSpeed)
	{
		moveFrameChangeCounter = 0;
		playerSprite.setTexture(playerTexture[moveFrame]);
		moveFrame++;
		if (moveFrame == AMOUNTFRAMES)
		{
			moveFrame = 0;
		}


	}
}

void Player::animateReload()
{
	reloadFrameChangeCounter++;
	if (reloadFrameChangeCounter > reloadAnimateSpeed)
	{
		reloadFrameChangeCounter = 0;
		playerSprite.setTexture(reloadTexture[reloadFrame]);
		reloadFrame++;
		if (reloadFrame == AMOUNTRELOADFRAMES)
		{
			reloadFrame = 0;

		}
	}
}

void Player::animateShooting()
{
	shootFrameChangeCounter++;

	if (shootFrameChangeCounter > shootAnimateSpeed)
	{
		shootFrameChangeCounter = 0;
		playerSprite.setTexture(shootingTexture[shootFrame]);
		shootFrame++;
		if (shootFrame == SHOOTSPRITEFRAMES)
		{
			shootFrame = 0;
		}

	}
}

void Player::resetShootingAnimation()
{
	shootFrame = 0;
	playerSprite.setTexture(shootingTexture[shootFrame]);
}

void Player::setPosition(sf::Vector2f t_newPos )
{
	playerSprite.setPosition(t_newPos);
}

void Player::updateUI(sf::View t_view)
{
	UItext.setPosition(t_view.getCenter() - sf::Vector2f(960, 540));
	stamBar.setPosition(t_view.getCenter() - sf::Vector2f(960,-500));
	damageSprite.setPosition(t_view.getCenter() - sf::Vector2f(960,540));
}

void Player::initialise()
{
	collisionBox.setFillColor(sf::Color::Magenta);
	collisionBox.setSize(sf::Vector2f(80, 60));
	collisionBox.setOrigin(sf::Vector2f(100 / 2, 40 / 2));


	if (!bloodTrailTexture.loadFromFile("ART/bloodTrail.png"))
	{
		std::cout << "error loading blood trail sprite" << std::endl;
	}
	
	for (int i = 0; i < 30; i++)

	{
		bloodTrailSprite[i].setTexture(bloodTrailTexture);
		bloodTrailSprite[i].setScale(.1, .1);
		bloodTrailSprite[i].setOrigin(bloodTrailSprite[i].getGlobalBounds().width / 2, bloodTrailSprite[i].getGlobalBounds().height / 2);
	}





	if (!damageTexture.loadFromFile("ART/damageEffect.png"))
	{
		std::cout << "error loading damage sprite" << std::endl;
	}

	damageSprite.setTexture(damageTexture);


	for (int i = 0; i < AMOUNTFRAMES; i++)
	{

		if (!playerTexture[i].loadFromFile("ART/player/Body/survivor-move_rifle_"+std::to_string(i)+".png"))
		{
			std::cout << "error loading file" << std::endl;
		}

		if (!legsTexture[i].loadFromFile("ART/player/legs/survivor-walk_"+std::to_string(i)+".png"))
		{
			std::cout << "error loading file" << std::endl;
		}
	}

	for (int i = 0; i < SHOOTSPRITEFRAMES; i++)
	{
		if (!shootingTexture[i].loadFromFile("ART/player/Shooting/survivor-shoot_rifle_" + std::to_string(i) + ".png"))
		{
			std::cout << "error loading file" << std::endl;
		}
	}

	for (int i = 0; i < AMOUNTRELOADFRAMES; i++)
	{
		if (!reloadTexture[i].loadFromFile("ART/player/Reloading/survivor-reload_rifle_" + std::to_string(i) + ".png"))
		{
			std::cout << "error loading file" << std::endl;
		}
	}
	
	legsSprite.setScale(.5, .5);
	

	playerSprite.setTexture(playerTexture[0]);
	playerSprite.setScale(.5, .5);
	playerSprite.setOrigin(playerSprite.getTextureRect().width / 2, playerSprite.getTextureRect().height / 2);
	
	legsSprite.setOrigin(playerSprite.getOrigin()+ sf::Vector2f(-30,-55));

	detectRadius.setRadius(MOVINGDETECTION);
	detectRadius.setOutlineColor(sf::Color::Black);
	detectRadius.setOutlineThickness(1);
	detectRadius.setFillColor(sf::Color::Transparent);

	detectOrigin = detectRadius.getOrigin() + sf::Vector2f(detectRadius.getRadius(), detectRadius.getRadius());

	detectRadius.setOrigin(detectOrigin);

	if (!playerFont.loadFromFile("ART/font.otf"))
	{
		//error
		std::cout << "could not load" << std::endl;
	}
	playerText.setFont(playerFont);
	playerText.setOutlineThickness(1);
	playerText.setOutlineColor(sf::Color::Black);
	playerText.setScale(0.75,0.75);

	if (!crosshairTexture.loadFromFile("ART/Cursor.png"))
	{
		//error
	}
	crosshairSprite.setTexture(crosshairTexture);

	


	stamBar.setFillColor(sf::Color::Green);
	stamBar.setSize(sf::Vector2f(3 * currentStamina, 35));
	stamBar.setPosition(5, 1065);

	UIfont.loadFromFile("ART/font.otf");
	UItext.setFont(UIfont);
	UItext.setFillColor(sf::Color::White);
	UItext.setString("INIT");

		
	for (int i = 0; i < MAXAMMOPERMAG; i++)
	{
		bullet[i].initialise(sf::Color::Red, sf::Vector2f(10,10), 25.0f);
	}

	std::cout << getPosition().x << ", " << getPosition().y << std::endl;
}

void Player::draw(sf::RenderWindow& t_window)
{
	t_window.draw(damageSprite);
	t_window.draw(UItext);
	t_window.draw(collisionBox);

	for (int i = 0; i < amountBloodStainsOut; i++)
	{
		t_window.draw(bloodTrailSprite[i]);
	}
	t_window.draw(legsSprite);
	t_window.draw(playerSprite);
	
	t_window.draw(crosshairSprite);
	t_window.draw(stamBar);
	t_window.draw(playerText);
	t_window.draw(detectRadius);
	



	for (int i = 0; i < MAXAMMOPERMAG; i++)
	{
		if (bullet[i].bulletState == Bullet::State::moving)
		{
			t_window.draw(bullet[i].bulletBody);
		}
	}
	
}

void Player::processInput()
{


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) == true && currentStamina >0)

	{
		processSprintInput();	
	}
	
	processNormalMove();
	processFireInput();
		

		
	
}

void Player::processSprintInput()
{
	bool keyPressed = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) == true)
	{
		playerSprite.move(-playerSpeed * 1.25, 0);
		keyPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) == true)
	{
		playerSprite.move(playerSpeed * 1.25, 0);
		keyPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) == true)
	{
		playerSprite.move(0, -playerSpeed * 1.25);
		keyPressed = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) == true)
	{
		playerSprite.move(0, playerSpeed * 1.25);
		keyPressed = true;
	}


	if (currentLives < 3)
	{
		currentStamina-= 0.1;
	}
}

void Player::processNormalMove()
{
	moving = false;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) == true )
	{
		playerSprite.move(-playerSpeed, 0);
		moving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) == true )
	{
		playerSprite.move(playerSpeed, 0);
		moving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) == true )
	{
		playerSprite.move(0, -playerSpeed);
		moving = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) == true)
	{
		playerSprite.move(0, playerSpeed);
		moving = true;
	}

	/*if (currentStamina < MAXSTAMINA && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) == false)
	{
		currentStamina += 0.5;
	}*/

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) == true && sf::Mouse::isButtonPressed(sf::Mouse::Left) == false && reloading == false && ammoInReserve >0)
	{
		reloadTimer = 0;
		reloading = true;
		playerText.setString("Reloading!");
		textTimeOut = 0;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R) && ammoInReserve == 0)
	{
		playerText.setString("Im out!");
		textTimeOut = 0;
	}

	if (moving && currentLives <3)
	{
		currentStamina -= 0.05;
	}
}

void Player::processFireInput()
{
	
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && rateOfFireLimit == ROFTIMEOUTCAP && reloading == false && ammoInMag >0)
	{
		
		for (int i = 0; i < MAXAMMOPERMAG; i++)
		{
			if (bullet[i].bulletState == Bullet::State::chambered && ammoInMag >0)
			{
				shooting = true;
				std::cout << "fired Bullet" << std::endl;
				bullet[i].fire(mouseRelativeToWindowPos, getPosition());
				ammoInMag--;
				std::cout << ammoInMag << std::endl;
				rateOfFireLimit = 0;
				break;
			}
		}
	}
	else
	{
		shooting = false;

	}
	
}

void Player::update(sf::RenderWindow& t_window)
{

	if (bloodTrailTimer.getElapsedTime() > sf::seconds(5) && currentLives <3)
	{
		bloodTrailSprite[amountBloodStainsOut].setPosition(this->getPosition());
		amountBloodStainsOut++;
		bloodTrailTimer.restart();
	}


	sf::Vector2i mousePosition = sf::Mouse::getPosition(t_window);
	mouseRelativeToWindowPos = t_window.mapPixelToCoords(mousePosition);
	collisionBox.setPosition(getPosition());

	std::cout << getPosition().x << ", " << getPosition().y << std::endl;


	playerRotationAngle = (sf::Vector2f)mouseRelativeToWindowPos - playerSprite.getPosition();

	if (thor::length(playerRotationAngle) > 5)
	{
		collisionBox.setRotation(thor::polarAngle(playerRotationAngle));
		playerSprite.setRotation(thor::polarAngle(playerRotationAngle));
		legsSprite.setRotation(thor::polarAngle(playerRotationAngle));
	}
	

	crosshairSprite.setPosition((sf::Vector2f)mouseRelativeToWindowPos);

	updateText();
	animate();
	processDetectionRadius();
	legsSprite.setPosition(getPosition());
	stamBar.setSize(sf::Vector2f(3 * currentStamina, 35));



	
	
	damageSprite.setColor (sf::Color(255, 0, 0, MAXSTAMINA - currentStamina));

	for (int i = 0; i < MAXAMMOPERMAG; i++)
	{
		bullet[i].update();
	}

	if (rateOfFireLimit < ROFTIMEOUTCAP)
	{
		rateOfFireLimit++;
	}

	if (reloading)
	{
		reload();
	}


	UItext.setString("MAGAZINE: " + std::to_string(ammoInMag) + "  " + "AMMO: " + std::to_string(ammoInReserve) + "   " 
		 "RELOADING: " + std::to_string(reloading) + "  " + "STAM: " + std::to_string(currentStamina)
			+"   "+ "LIVES: " + std::to_string(currentLives) + " MOUSEPOS: " + std::to_string(mousePosition.x) + " , " + std::to_string(mousePosition.y)
			+ "  "   + "AMMOINMAG: " + std::to_string(ammoInMag)
			+ "  " + "total: " + std::to_string(ammoInReserve));
}

void Player::reload()
{
	
	if (ammoInReserve > 0)
	{
		if (reloadTimer < 120)
		{
			reloadTimer++;
		}
		else
		{
			refillAmmo();
		}
	}
}

void Player::refillAmmo()
{
	for (int i = 0; i < MAXAMMOPERMAG; i++)
	{
		bullet[i].bulletState = Bullet::State::fired;

	}


	ammoInReserve += ammoInMag;
	ammoInMag = 0;



	if (ammoInReserve >= MAXAMMOPERMAG)
	{
		for (int i = 0; i < MAXAMMOPERMAG; i++)
		{

			
			bullet[i].bulletState = Bullet::State::chambered;
		}
		ammoInMag = MAXAMMOPERMAG;
		reloading = false;
		ammoInReserve -= MAXAMMOPERMAG;
		reloadTimer = 0;
	}
	else
	{
		for (int i = 0; i < ammoInReserve; i++)
		{
			ammoInMag = ammoInReserve;		
			
			bullet[i].bulletState = Bullet::State::chambered;
		}
		reloading = false;
		ammoInReserve = 0;
	}

}

void Player::processDetectionRadius()
{
	if (moving && sf::Keyboard::isKeyPressed(sf::Keyboard::LShift))
	{
		animateLegsWalking();
		detectRadius.setRadius(320);
		detectRadius.setOrigin(sf::Vector2f(detectRadius.getRadius(), detectRadius.getRadius()));
		detectRadius.setPosition(getPosition());

	}

	else if (moving)
	{
		animateLegsWalking();
		detectRadius.setRadius(220);
		detectRadius.setOrigin(sf::Vector2f(detectRadius.getRadius(), detectRadius.getRadius()));
		detectRadius.setPosition(getPosition());

	}


	else
	{
		detectRadius.setRadius(60);
		detectRadius.setOrigin(sf::Vector2f(detectRadius.getRadius(), detectRadius.getRadius()));
		detectRadius.setPosition(getPosition());
	}

	if(sf::Mouse::isButtonPressed(sf::Mouse::Left)&& ammoInMag >0 && reloading == false)
		
	{
		detectRadius.setRadius(500);
		detectRadius.setOrigin(sf::Vector2f(detectRadius.getRadius(), detectRadius.getRadius()));
		detectRadius.setPosition(getPosition());
	}
}

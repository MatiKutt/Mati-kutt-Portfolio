#include "Zombie.h"

void Zombie::stopProjectile()
{
	zombieProjectile.bulletState = Bullet::State::fired;
	firingCooldown.restart();
}

void Zombie::updateVisionCone()
{
	m_arrowLeft.setColor(sf::Color::Red);
	m_arrowRight.setColor(sf::Color::Red);

	sf::Vector2f leftArrowEndWhenAggro = thor::rotatedVector(lastKnownPlayerPos - zombieSprite.getPosition(), -17.50f);
	sf::Vector2f rightArrowEndWhenAggro = thor::rotatedVector(lastKnownPlayerPos - zombieSprite.getPosition(), 17.50f);

	thor::setLength(leftArrowEndWhenAggro, 600.0f);
	thor::setLength(rightArrowEndWhenAggro, 600.0f);
	m_arrowLeft.setDirection(leftArrowEndWhenAggro);
	m_arrowRight.setDirection(rightArrowEndWhenAggro);

}

void Zombie::turnToPlayer(sf::Vector2f t_playerPos)
{
	velocity = lastKnownPlayerPos - zombieSprite.getPosition();
	thor::setLength(velocity, speed);
	zombieSprite.setRotation(thor::polarAngle(lastKnownPlayerPos - zombieSprite.getPosition()));
	collisionBox.setRotation(thor::polarAngle(lastKnownPlayerPos - zombieSprite.getPosition()));
}

void Zombie::processFollowPlayer(sf::Vector2f t_playerPos)
{
	

	//std::cout << "Zombie moves to your last known location" << std::endl;

	



	turnToPlayer(t_playerPos);
	

	updateVisionCone();
	
	if ((area1 + area2 + area3) == areaOrig && lineInterrupted == false)
	{
		if (firingCooldown.getElapsedTime() > sf::seconds(3)
			&& thor::length(t_playerPos - getPosition()) < 200.0f)
		{
			zombieProjectile.fire(lastKnownPlayerPos, this->getPosition());
			firingCooldown.restart();
		}

		currentState = State::following;
		lastKnownPlayerPos = t_playerPos;
		//std::cout << "You are seen" << std::endl;
	}
}

void Zombie::processIdle(sf::Vector2f t_playerPos)
{
	m_arrowLeft.setDirection(VISION_CONE_LENGTH * thor::rotatedVector(m_visionConeDir, baseConeRotation));
	m_arrowRight.setDirection(VISION_CONE_LENGTH * thor::rotatedVector(m_visionConeDir, baseConeRotation + 75));
	baseConeRotation += 0.25;
	m_arrowLeft.setColor(sf::Color::Green);
	m_arrowRight.setColor(sf::Color::Green);
	//error checking for values == 0 on game start
	bool canCheckIfInCone = true;
	if (areaOrig == 0)
	{
		canCheckIfInCone = false;
	}

	if ((area1 + area2 + area3) == areaOrig && lineInterrupted == false)
	{
		

		currentState = State::following;
		if (canCheckIfInCone)
		{
			lastKnownPlayerPos = t_playerPos;		
		}
		else

		{
			currentState = State::Idle;
			lastKnownPlayerPos = this->getPosition();
		}
	}
	else
	{
		currentState = State::Idle;
	}


	if (idleTimer.getElapsedTime() > sf::seconds(15))
	{
		currentState = State::patrolling;
	}
}

void Zombie::updateCone(sf::RectangleShape t_playerCollisionBox)
{
	m_arrowLeft.setPosition(zombieSprite.getPosition());
	m_arrowRight.setPosition(zombieSprite.getPosition());
	int x1 = zombieSprite.getPosition().x;
	int y1 = zombieSprite.getPosition().y;

	int x2 = (m_arrowLeft.getPosition() + (m_arrowLeft.getDirection())).x;
	int y2 = (m_arrowLeft.getPosition() + (m_arrowLeft.getDirection())).y;

	int x3 = (m_arrowRight.getPosition() + (m_arrowRight.getDirection())).x;
	int y3 = (m_arrowRight.getPosition() + (m_arrowRight.getDirection())).y;



	int px = t_playerCollisionBox.getPosition().x;
	int py = t_playerCollisionBox.getPosition().y;


	areaOrig = abs((x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1));
	area1 = abs((x1 - px) * (y2 - py) - (x2 - px) * (y1 - py));
	area2 = abs((x2 - px) * (y3 - py) - (x3 - px) * (y2 - py));
	area3 = abs((x3 - px) * (y1 - py) - (x1 - px) * (y3 - py));




}

void Zombie::updateLineToPlayer(sf::Vector2f t_playerPos, sf::RectangleShape t_wall)
{
	sf::Vector2f vectorBetween = t_playerPos - this->getPosition();
	lineToPlayer.setPosition(this->getPosition());
	lineToPlayer.setSize(sf::Vector2f(1, thor::length(vectorBetween)));
	lineToPlayer.setRotation(-90 + thor::polarAngle(vectorBetween));
	if (lineToPlayer.getGlobalBounds().intersects(t_wall.getGlobalBounds()))
	{
		lineInterrupted = true;
	}
	else
	{
		lineInterrupted = false;
	}
	
}

void Zombie::init()
{
	for (int i = 0; i < 16; i++)
	{
		if (!zombieIdleTexture[i].loadFromFile("ART/Zombie/Idle/skeleton-idle_" + std::to_string(i) + ".png"))
		{
			//error
		}
		if (!zombieMoveTexture[i].loadFromFile("ART/Zombie/Move/skeleton-move_" + std::to_string(i) + ".png"))
		{
			//error
		}
		
	}
	for (int  i = 0; i < 8; i ++)
	{
		if (!zombieAttackTexture[i].loadFromFile("ART/Zombie/Attack/skeleton-attack_" + std::to_string(i) + ".png"))
		{
			//error
		}
	}
	
	zombieSprite.setScale(0.47, 0.47);
	zombieSprite.setRotation(0);
	zombieSprite.setOrigin(120, 110);


	zombieProjectile.initialise(sf::Color::Green, sf::Vector2f(20,20), 3.0f);
	collisionBox.setFillColor(sf::Color::Magenta);
	collisionBox.setSize(sf::Vector2f(80, 80));
	collisionBox.setOrigin(sf::Vector2f(80 / 2, 80 / 2));
	collisionBox.setPosition(sf::Vector2f(rand()%1920, rand()%1080) + sf::Vector2f(0,20));
	lastKnownPlayerPos = collisionBox.getPosition();
	
}

void Zombie::draw(sf::RenderWindow& t_window)
{
	if (alive)
	{
		if (lineInterrupted)
		{
			lineToPlayer.setFillColor(sf::Color::Red);
		}
		else
		{
			lineToPlayer.setFillColor(sf::Color::Green);
		}
		t_window.draw(zombieProjectile.bulletBody);
		t_window.draw(collisionBox);
		t_window.draw(zombieSprite);
		t_window.draw(m_arrowLeft);
		t_window.draw(m_arrowRight);
		t_window.draw(lineToPlayer);
	}
}

void Zombie::update(sf::Vector2f t_playerPos, int t_detectionRadius, sf::RectangleShape t_playerCollisionBox)
{
	if (alive)
	{

		zombieProjectile.update();
		updateCone(t_playerCollisionBox);


		// to avoid state switch mid attack
		if (finishedAttacking)
		{

			//currentState = State::Idle;

			//if zombie can hear player
			if (thor::length(t_playerPos - zombieSprite.getPosition()) <= t_detectionRadius)
			{
				lastKnownPlayerPos = t_playerPos;
				currentState = State::following;
			}


			//if idling, stay in place and scan area
			if (currentState == State::Idle)
			{

				processIdle(t_playerPos);

			}

			else if (currentState == State::following)
			{
				processFollowPlayer(t_playerPos);
			}


			if (collisionBox.getGlobalBounds().intersects(t_playerCollisionBox.getGlobalBounds()))
			{
				finishedAttacking = false;
				currentState = State::attacking;
			}


			if (currentState == State::patrolling)
			{
				idleTimer.restart();
				lastKnownPlayerPos = getPosition() + sf::Vector2f(rand() % 400 + (-200), rand() % 400 + (-200));
				currentState = State::following;
				
			}

			zombieSprite.setPosition(collisionBox.getPosition());

		}




		animate();
	}
	
}
	



void Zombie::animate()
{
	if (MathUtility::distance(sf::Vector2f(zombieSprite.getPosition()), lastKnownPlayerPos) < 60)
	{
		currentState = State::Idle;
	}


	if (currentState == State::following)
	{
		collisionBox.move(velocity);
		zombieSprite.setTextureRect(sf::IntRect(0,0,288,311));
		frameCountDown++;
		if (frameCountDown == animateSpeed)
		{
			frameCountDown = 0;
			zombieSprite.setTexture(zombieMoveTexture[currentMoveFrame]);
			currentMoveFrame++;
			if (currentMoveFrame == AMOUNTTEXTURES)
			{
				currentMoveFrame = 0;
			}
		}

	}
	else if (currentState == State::Idle)
	{
		zombieSprite.setTextureRect(sf::IntRect(0, 0, 241, 222));
		frameCountDown++;
		if (frameCountDown == animateSpeed)
		{
			frameCountDown = 0;
			zombieSprite.setTexture(zombieIdleTexture[currentMoveFrame]);
			currentMoveFrame++;
			if (currentMoveFrame == AMOUNTTEXTURES)
			{
				currentMoveFrame = 0;
			}
		}
	}

	else if (currentState == State::attacking)
	{
		//std::cout << "enemy attacks you " << std::endl;
		zombieSprite.setTextureRect(sf::IntRect(0, 0, 318, 294));
		attackFrameCountDown++;
		if (attackFrameCountDown == ATTACKANIMATESPEED)
		{
			attackFrameCountDown = 0;
			zombieSprite.setTexture(zombieAttackTexture[currentAttackFrame]);
			currentAttackFrame++;
			{
				if (currentAttackFrame == AMOUNTATTACKTEXTURES)
				{
					finishedAttacking = true;
					currentAttackFrame = 0;
					currentState = State::following;
					
				}
			}
		}
	}
}

void Zombie::moveRandomly()
{


}

void Zombie::setPosition(sf::Vector2f t_pos)
{
	collisionBox.setPosition(t_pos);
}

sf::Vector2f Zombie::getPosition()
{
	return collisionBox.getPosition();
}

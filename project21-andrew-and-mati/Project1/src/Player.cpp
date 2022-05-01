#include "Player.h"
#include "Game.h"

Player::Player()
{
	rays.reserve(xRes);

	for (float i = 0; i < xRes / 5; i++)
	{
		rays.push_back(new Ray(i / 3.2));
		thor::rotate(rays[i]->m_dir, -25.0f);
	}
	for (int i = 0; i < MAXAMMOPERMAG; i++)
	{
		bullets[i].initialise(sf::Color::Red, sf::Vector2f(10, 10), 12);
	}


	flashTexture.loadFromFile("./recources/TEXTURES/WeaponSprites/flash.png");
	flashSprite.setTexture(flashTexture);

	flashSprite.setOrigin(sf::Vector2f(flashSprite.getGlobalBounds().width / 2, flashSprite.getGlobalBounds().height / 2));
	flashSprite.setPosition(xRes / 2 + 50, yRes / 2);



	gunShotBuffer.loadFromFile("./recources/SOUNDS/gunshot.wav");
	gunShot.setBuffer(gunShotBuffer);
	gunShot.setVolume(25);

	collisionBox.setSize(sf::Vector2f(5, 5));
	collisionBox.setFillColor(sf::Color::Cyan);
	collisionBox.setOrigin(collisionBox.getGlobalBounds().width / 2, collisionBox.getGlobalBounds().height / 2);
}

Player::~Player()
{
	
}

void Player::movePlayer()
{
	if (canMove)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			for (int i = 0; i < rays.size(); i++)
			{
				thor::rotate(rays[i]->m_dir, 1.0f);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			for (int i = 0; i < rays.size(); i++)
			{
				thor::rotate(rays[i]->m_dir, -1.0f);
			}
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
		{
			for (int i = 0; i < rays.size(); i++)
			{
				rays[i]->source += (rays[rays.size() / 2]->m_dir);
			}
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			for (int i = 0; i < rays.size(); i++)
			{
				rays[i]->source -= rays[rays.size() / 2]->m_dir;
			}
		}
	}
}

void Player::update(Grid* grid)
{
	if (oldCell == nullptr) 
	{
		oldCell = grid->GetIntersects(playerPos);
	}

	//collisionBox.setRotation(thor::polarAngle(rays[rays.size() / 2]->m_dir));
	collisionBox.setPosition(getPosition());
	processFireInput();
	for (int i = 0; i < MAXAMMOPERMAG; i++)
	{
		bullets[i].update();
	}

	for (int i = 0; i < MAXAMMOPERMAG; i++)
	{
		bullets[i].update();
	}

	if (rateOfFireLimit < ROFTIMEOUTCAP)
	{
		rateOfFireLimit++;
	}

	if (reloading)
	{
		reload();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::P))
	{
		if (pints > 0)
		{
			health += 2;
			pints--;
		}
	}

	if(health <= 0) 
	{
		Game::currentState = GameState::Death;
	}


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
	/*for (int i = 0; i < MAXAMMOPERMAG; i++)
	{
		bullets[i].bulletState = Bullet::State::fired;

	}


	ammoInReserve += ammoInMag;
	ammoInMag = 0;



	if (ammoInReserve >= MAXAMMOPERMAG)
	{
		for (int i = 0; i < MAXAMMOPERMAG; i++)
		{


			bullets[i].bulletState = Bullet::State::chambered;
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

			bullets[i].bulletState = Bullet::State::chambered;
		}
		reloading = false;
		ammoInReserve = 0;
	}*/

	ammoInMag += 30;

}

int Player::getAmmo()
{
	return ammoInMag;
}

void Player::addPints()
{
	pints++;
}

void Player::addHealth()
{
	health++;
}

int Player::getPints()
{
	return pints;
}

int Player::getHealth()
{
	return health;
}

void Player::processFireInput()
{
	

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && rateOfFireLimit == ROFTIMEOUTCAP && reloading == false && ammoInMag > 0)
	{

		for (int i = 0; i < MAXAMMOPERMAG; i++)
		{
			if (bullets[i].bulletState == Bullet::State::chambered && ammoInMag > 0)
			{
				gunShot.play();
				shooting = true;
				std::cout << "fired Bullet" << std::endl;
				bullets[i].fire((rays[rays.size() / 2]->m_dir + getPosition()), getPosition());
				ammoInMag--;
				std::cout << ammoInMag << std::endl;
				rateOfFireLimit = 0;
				flashOn = true;
				flashSprite.rotate(rand());
				break;
			}
		}
	}

	if (rateOfFireLimit == ROFTIMEOUTCAP)
	{
		flashOn = false;
	}

	else
	{
		shooting = false;

	}

}

sf::Vector2f Player::getPosition()
{
	return rays[0]->source;
}

void Player::setPosition(sf::Vector2f t_newPos)
{
	for (int i = 0; i < rays.size(); i++)
	{
		rays[i]->source = t_newPos;
	}
}

void Player::draw(sf::RenderWindow& t_window, std::vector<Boundary*> walls, std::vector<BillboardedBoundary*> sprites, std::vector<sf::RectangleShape*> spritePlane,std::vector<EnemyOne*> enemys)
{
	t_window.draw(collisionBox);

	for (int i = 0; i < rays.size(); i++) {
		rays[i]->hitSprite = false;
		rays[i]->hitEnemy = false;

		sf::Vector2f closestWall = sf::Vector2f(INFINITY,INFINITY);
		float record = INFINITY;
		int walltoRender = 0;

		sf::Vector2f closestSprite = sf::Vector2f(INFINITY, INFINITY);
		float spriteRecord = INFINITY;
		int spriteToRender = 0;

		sf::Vector2f closestEnemy = sf::Vector2f(INFINITY, INFINITY);
		float enemyRecord = INFINITY;
		int EnemyToRender = 0;

		for ( auto& wall : walls) 
		{
			sf::Vector2f pt = rays[i]->cast(*wall);
			if (pt != sf::Vector2f(INFINITY,INFINITY))
			{
				const float d = thor::length(this->rays[i]->source - pt);
				if (d < record)
			{
					record = d;
					closestWall = pt;
					walltoRender = wall->texture;
					rays[i]->storeWall(*wall);
			}

			}
		}


		for (auto& sprite : sprites)
		{
			sf::Vector2f pt = rays[i]->castAtSprite(sprite);
			if (pt != sf::Vector2f(INFINITY, INFINITY))
			{
				const float d = thor::length(this->rays[i]->source - pt);
				if (d < spriteRecord)
				{
					spriteRecord = d;
					closestSprite = pt;
					rays[i]->hitSprite = true;
					rays[i]->spriteHitDistance = pt;
					rays[i]->spriteToRender = sprite->texture;
					spriteToRender = sprite->texture;
					rays[i]->storeSprite(*sprite);
					
				}
			}
			
		}

		for (auto& enemy : enemys)
		{
			sf::Vector2f pt = rays[i]->castAtEnemy(enemy);
	
			if (pt != sf::Vector2f(INFINITY, INFINITY))
			{
				const float d = thor::length(this->rays[i]->source - pt);
				
				if (d < enemyRecord)
				{
					enemyRecord = d;
					closestEnemy = pt;
					rays[i]->hitEnemy = true;
					rays[i]->enemyHitDistance = pt;
					rays[i]->enemyToRender = enemy->getSprite()->texture;
					rays[i]->storeEnemy(*enemy);
				}
			}
		}

		if (closestWall != sf::Vector2f(INFINITY,INFINITY))
		{
			rays[i]->textureToRender = walltoRender;
			rays[i]->draw(t_window); // draw drawable element
		}

		if (closestSprite != sf::Vector2f(INFINITY, INFINITY))
		{
			
			rays[i]->spriteToRender = spriteToRender;
			
		}


		rays[i]->spriteHitDistance = closestSprite;
 		rays[i]->intersectionPoint = closestWall;
	}

	for (auto& bullet : bullets)
	{
		t_window.draw(bullet.bulletBody);
	}
}


std::vector<Ray*> Player::getrays()
{
	return rays;
}

//void Player::pickupItem(pickupType t_type)
//{
//	switch (t_type)
//	{
//	default:
//		break;
//	case pickupType::Ammo:
//		this->reload();
//		break;
//	case pickupType::Health:
//		//add health
//		break;
//
//	case pickupType::Pint:
//		//add pint
//		break;
//
//	case pickupType::Weapon:
//		// give next weapon
//		break;
//
//
//	}
//}

void Player::setupPlayer()
{
	
}

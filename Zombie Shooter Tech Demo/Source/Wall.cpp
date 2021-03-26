#include "Wall.h"

//all of the collisions are absolute garbage code but FUNCTIONAL garbage code
//NEED REFACTOR FOR ENTIRE CLASS


void Wall::checkCollisionsWithPlayer(Player &t_player)
{
	
	
	if (t_player.collisionBox.getGlobalBounds().intersects(body.getGlobalBounds()))
	{

	
		t_player.setPosition(lastKnownPlayerPos);
		
		if (t_player.collisionBox.getPosition().x < body.getPosition().x)
		{
			t_player.setPosition(t_player.getPosition() - sf::Vector2f(1, 0));
		}
		if (t_player.collisionBox.getPosition().x > body.getPosition().x)
		{
			t_player.setPosition(t_player.getPosition() + sf::Vector2f(1, 0));
		}


		if (t_player.collisionBox.getPosition().y < body.getPosition().y)
		{
			t_player.setPosition(t_player.getPosition() - sf::Vector2f(0, 1));
		}
		if (t_player.collisionBox.getPosition().y > body.getPosition().x)
		{
			t_player.setPosition(t_player.getPosition() + sf::Vector2f(0, 1));
		}
	}

	for (int i = 0; i < t_player.MAXAMMOPERMAG; i++)
	{
		if (t_player.bullet[i].bulletState == Bullet::State::moving)
		{
			if (t_player.bullet[i].bulletBody.getGlobalBounds().intersects(body.getGlobalBounds()))
			{
				t_player.bullet[i].bulletState = Bullet::State::fired;
			}
		}
	}
	
	lastKnownPlayerPos = t_player.getPosition();
}

void Wall::checkCollisionsWithEnemy(Zombie& t_zombie)
{
	lastKnownZombiePos = t_zombie.getPosition();
	if (t_zombie.collisionBox.getGlobalBounds().intersects(body.getGlobalBounds()))
	{


		t_zombie.setPosition(lastKnownZombiePos);

		if (t_zombie.collisionBox.getPosition().x < body.getPosition().x)
		{
			t_zombie.setPosition(t_zombie.getPosition() - sf::Vector2f(1, 0));
		}
		if (t_zombie.collisionBox.getPosition().x > body.getPosition().x)
		{
			t_zombie.setPosition(t_zombie.getPosition() + sf::Vector2f(1, 0));
		}


		if (t_zombie.collisionBox.getPosition().y < body.getPosition().y)
		{
			t_zombie.setPosition(t_zombie.getPosition() - sf::Vector2f(0, 1));
		}
		if (t_zombie.collisionBox.getPosition().y > body.getPosition().x)
		{
			t_zombie.setPosition(t_zombie.getPosition() + sf::Vector2f(0, 1));
		}
		t_zombie.lastKnownPlayerPos = lastKnownZombiePos;
	}



	

}




void Wall::draw(sf::RenderWindow& t_window)
{
	t_window.draw(body);
}

#pragma once
#include "Boundary.h"
#include "Player.h"

class Cube
{
public:
	//Cube() {};

	
	Cube(sf::Vector2f position, int texture)
	{
		sides[0].startPoint = position;
		sides[0].endPoint = sf::Vector2f(position.x, position.y + 32);

		sides[1].startPoint = sides[0].endPoint;
		sides[1].endPoint = sf::Vector2f(sides[1].startPoint.x + 32, sides[1].startPoint.y);

		sides[2].startPoint = sides[1].endPoint;
		sides[2].endPoint = sf::Vector2f(sides[2].startPoint.x, sides[1].endPoint.y - 32);

		sides[3].startPoint = sides[2].endPoint;
		sides[3].endPoint = sides[0].startPoint;

		for (int i = 0; i < 4; i++)
		{
			sides[i].texture = texture;
		}

		body.setPosition(sides[0].startPoint);
		body.setSize(sf::Vector2f(32, 32));
		
	}

	void setPosition(sf::Vector2f t_newPos)
	{
		body.setPosition(t_newPos);
	}

	bool checkCollisionsWithPlayer(Player& t_player)
	{
		//sf::Vector2f lastKnownPlayerPos = t_player.getPosition();

		if (t_player.collisionBox.getGlobalBounds().intersects(body.getGlobalBounds()))
		{
			
			//t_player.canMove = false;



			if (body.getSize().x > body.getSize().y)
			{
				if (t_player.collisionBox.getPosition().y < body.getPosition().y)
				{
					t_player.setPosition(t_player.getPosition() - sf::Vector2f(0, 2));
				}
				if (t_player.collisionBox.getPosition().y > body.getPosition().y)
				{
					t_player.setPosition(t_player.getPosition() + sf::Vector2f(0, 2));
				}
			}



			if (body.getSize().y > body.getSize().x)
			{
				if (t_player.collisionBox.getPosition().x < body.getPosition().x)
				{
					t_player.setPosition(t_player.getPosition() - sf::Vector2f(2, 0));
				}
				if (t_player.collisionBox.getPosition().x > body.getPosition().x)
				{
					t_player.setPosition(t_player.getPosition() + sf::Vector2f(2, 0));
				}
			}

			if (body.getSize().y == body.getSize().x)
			{
				sf::Vector2f lineBetween = this->body.getPosition() - t_player.getPosition() + this->body.getSize() / 2.0f;
				thor::setLength(lineBetween, -2.0f);


				t_player.setPosition(t_player.getPosition() + lineBetween);

			}
			return true;
		}
		else
			return false;
	/*	else
		{

			t_player.canMove = true;
		}*/

		


	

	}
	sf::RectangleShape body;
	Boundary sides[4];
};


#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Boundary
{
public:

	Boundary();

	Boundary(sf::Vector2f t_startP, sf::Vector2f t_endP, int t_texture) : endPoint(t_endP), startPoint(t_startP), texture(t_texture)
	{
	
	};

	


	int texture;
	sf::Vector2f startPoint;
	sf::Vector2f endPoint;
	

	void draw(sf::RenderWindow& t_window)
	{
		sf::Vertex line[] =
		{
		sf::Vertex(startPoint,sf::Color::Red),
		sf::Vertex(endPoint,sf::Color::Red)
		};

		t_window.draw(line, 2, sf::Lines);
	}
};
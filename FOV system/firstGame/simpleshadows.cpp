//mati kutt shadows
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h> 
#include <time.h> 
#include <vector>
#include "Trigonometry.hpp"
#include "VectorAlgebra2D.h"

int main()
{
	
	sf::VertexArray shadowQuad1(sf::Quads, 4);
	sf::VertexArray shadowQuad2(sf::Quads, 4);
	sf::VertexArray shadowQuad3(sf::Quads, 4);
	sf::VertexArray shadowQuad4(sf::Quads, 4);

	sf::VertexArray shadowSecondQuad1(sf::Quads, 4);
	sf::VertexArray shadowSecondQuad2(sf::Quads, 4);
	sf::VertexArray shadowSecondQuad3(sf::Quads, 4);
	sf::VertexArray shadowSecondQuad4(sf::Quads, 4);


	sf::RenderWindow window(sf::VideoMode(800, 600), "2d lighting -simple shadows");

	sf::VertexArray line(sf::Lines);

	srand(time(NULL));
	sf::VertexArray quad(sf::Quads, 4);
	sf::VertexArray quad1(sf::Quads, 4);
	sf::Vector2f light = { 100,100 };
	sf::CircleShape lightShape(5);
	lightShape.setOrigin(5, 5);
	lightShape.setPosition(0, 0);
	lightShape.setFillColor(sf::Color::White);


	for (int i = 0; i < 4; i++)
	{
	
		shadowQuad1[i].color = sf::Color::Black;
		shadowQuad2[i].color = sf::Color::Black;
		shadowQuad3[i].color = sf::Color::Black;
		shadowQuad4[i].color = sf::Color::Black;

		shadowSecondQuad1[i].color = sf::Color::Black;
		shadowSecondQuad2[i].color = sf::Color::Black;
		shadowSecondQuad3[i].color = sf::Color::Black;
		shadowSecondQuad4[i].color = sf::Color::Black;

	}

	quad[0].position = sf::Vector2f(300.f, 300);
	quad[1].position = sf::Vector2f(500.f, 300.f);
	quad[2].position = sf::Vector2f(500.f, 400.f);
	quad[3].position = sf::Vector2f(300.f, 400.f);
	quad[0].color = sf::Color::Green;
	quad[1].color = sf::Color::Red;
	quad[2].color = sf::Color::Red;
	quad[3].color = sf::Color::Red;

	quad1[0].position = sf::Vector2f(200, 150);
	quad1[1].position = sf::Vector2f(300.f, 150.f);
	quad1[2].position = sf::Vector2f(300.f, 220.f);
	quad1[3].position = sf::Vector2f(200.f, 220.f);
	quad1[0].color = sf::Color::Red;
	quad1[1].color = sf::Color::White;
	quad1[2].color = sf::Color::Red;
	quad1[3].color = sf::Color::Red;

	sf::ConvexShape newShape;
	newShape.setFillColor(sf::Color::Black);
	newShape.setPointCount(30);
	// set timePerFrame to 1 60th of a second. 60 frames per second
	sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	// the clock object keeps the time.
	sf::Clock clock;
	clock.restart();

	while (window.isOpen())
	{
		// check if the close window button is clicked on.
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//add to the time since last update and restart the clock
		timeSinceLastUpdate += clock.restart();

		//update every 60th of a second
		//only when the time since last update is greater than 1/60 update the world.

		if (timeSinceLastUpdate > timePerFrame)
		{
			sf::Vector2i position = sf::Mouse::getPosition(window);

			lightShape.setPosition(position.x, position.y);

			
			
			window.clear(sf::Color::Blue);
			window.draw(shadowQuad1);
			window.draw(shadowQuad2);
			window.draw(shadowQuad3);
			window.draw(shadowQuad4);
			window.draw(shadowSecondQuad1);
			window.draw(shadowSecondQuad2);
			window.draw(shadowSecondQuad3);
			window.draw(shadowSecondQuad4);
			window.draw(quad);
			window.draw(quad1);
			window.draw(lightShape);
			//window.draw(line);
			line.clear();
			sf::Vector2f lineToVertex1 = quad1[0].position - lightShape.getPosition();
			sf::Vector2f lineToVertex2 = quad1[1].position - lightShape.getPosition();
			sf::Vector2f lineToVertex3 = quad1[2].position - lightShape.getPosition();
			sf::Vector2f lineToVertex4 = quad1[3].position - lightShape.getPosition();
			
			sf::Vector2f lineToVertex5 = quad[0].position - lightShape.getPosition();
			sf::Vector2f lineToVertex6 = quad[1].position - lightShape.getPosition();
			sf::Vector2f lineToVertex7 = quad[2].position - lightShape.getPosition();
			sf::Vector2f lineToVertex8 = quad[3].position - lightShape.getPosition();



			//first shadow quad points on the rectangle
			shadowQuad1[0].position = lineToVertex1 + lightShape.getPosition();
			shadowQuad1[1].position = lineToVertex2 + lightShape.getPosition();



			shadowQuad2[0].position = lineToVertex3 + lightShape.getPosition();
			shadowQuad2[1].position = lineToVertex4 + lightShape.getPosition();


			shadowQuad3[0].position = lineToVertex1 + lightShape.getPosition();
			shadowQuad3[1].position = lineToVertex3 + lightShape.getPosition();


			shadowQuad4[0].position = lineToVertex2 + lightShape.getPosition();
			shadowQuad4[1].position = lineToVertex4 + lightShape.getPosition();

			//second shadow quad points on the rectangle
			shadowSecondQuad1[0].position = lineToVertex5 + lightShape.getPosition();
			shadowSecondQuad1[1].position = lineToVertex6 + lightShape.getPosition();



			shadowSecondQuad2[0].position = lineToVertex7 + lightShape.getPosition();
			shadowSecondQuad2[1].position = lineToVertex8 + lightShape.getPosition();


			shadowSecondQuad3[0].position = lineToVertex5 + lightShape.getPosition();
			shadowSecondQuad3[1].position = lineToVertex7 + lightShape.getPosition();


			shadowSecondQuad4[0].position = lineToVertex6 + lightShape.getPosition();
			shadowSecondQuad4[1].position = lineToVertex8 + lightShape.getPosition();

			// changle length of vector from lightsource to rectangle points
			thor::setLength(lineToVertex1, 1600.0f);
			thor::setLength(lineToVertex2, 1600.0f);
			thor::setLength(lineToVertex3, 1600.0f);
			thor::setLength(lineToVertex4, 1600.0f);

			thor::setLength(lineToVertex5, 1600.0f);
			thor::setLength(lineToVertex6, 1600.0f);
			thor::setLength(lineToVertex7, 1600.0f);
			thor::setLength(lineToVertex8, 1600.0f);


			//first shadow quad end points after changing length
			shadowQuad3[2].position = lineToVertex3 + lightShape.getPosition();
			shadowQuad3[3].position = lineToVertex1 + lightShape.getPosition();


			shadowQuad4[2].position = lineToVertex4 + lightShape.getPosition();
			shadowQuad4[3].position = lineToVertex2 + lightShape.getPosition();


			shadowQuad2[2].position = lineToVertex4 + lightShape.getPosition();
			shadowQuad2[3].position = lineToVertex3 + lightShape.getPosition();

			shadowQuad1[2].position = lineToVertex2 + lightShape.getPosition();
			shadowQuad1[3].position = lineToVertex1 + lightShape.getPosition();

			//second shadow quad end points after changing length
			shadowSecondQuad1[2].position = lineToVertex6 + lightShape.getPosition();
			shadowSecondQuad1[3].position = lineToVertex5 + lightShape.getPosition();


			shadowSecondQuad2[2].position = lineToVertex8 + lightShape.getPosition();
			shadowSecondQuad2[3].position = lineToVertex7 + lightShape.getPosition();


			shadowSecondQuad3[2].position = lineToVertex7 + lightShape.getPosition();
			shadowSecondQuad3[3].position = lineToVertex5 + lightShape.getPosition();

			shadowSecondQuad4[2].position = lineToVertex8 + lightShape.getPosition();
			shadowSecondQuad4[3].position = lineToVertex6 + lightShape.getPosition();




			//FIRST QUAD LINES
			line.append(sf::Vertex(lightShape.getPosition(), sf::Color::White));
			line.append(sf::Vertex(lightShape.getPosition() +lineToVertex1, sf::Color::White));
			
			line.append(sf::Vertex(lightShape.getPosition(), sf::Color::White));
			line.append(sf::Vertex(lightShape.getPosition() + lineToVertex2, sf::Color::White));

			line.append(sf::Vertex(lightShape.getPosition(), sf::Color::White));
			line.append(sf::Vertex(lightShape.getPosition() + lineToVertex3, sf::Color::White));

			line.append(sf::Vertex(lightShape.getPosition(), sf::Color::White));
			line.append(sf::Vertex(lightShape.getPosition() + lineToVertex4, sf::Color::White));

			//SECOND QUAD LINES


			lineToVertex1 = quad[0].position - lightShape.getPosition();
			lineToVertex2 = quad[1].position - lightShape.getPosition();
			lineToVertex3 = quad[2].position - lightShape.getPosition();
			lineToVertex4 = quad[3].position - lightShape.getPosition();

			
			


			thor::setLength(lineToVertex1, 200.0f);
			thor::setLength(lineToVertex2, 200.0f);
			thor::setLength(lineToVertex3, 200.0f);
			thor::setLength(lineToVertex4, 200.0f);





			newShape.setPoint(0, quad1[0].position - lightShape.getPosition());
			newShape.setPoint(1, lineToVertex1);
			newShape.setPoint(2, quad1[1].position - lightShape.getPosition());
			newShape.setPoint(3, lineToVertex1);
			newShape.setPoint(4, quad1[2].position - lightShape.getPosition());
			newShape.setPoint(5, lineToVertex1);
			newShape.setPoint(6, quad1[3].position - lightShape.getPosition());
			
			
			
			newShape.setPoint(7, lineToVertex1);

	
			
			
			window.display();
			
			// reset the timeSinceLastUpdate to 0 
			timeSinceLastUpdate = sf::Time::Zero;
		}
	}

	return 0;
}

//First physics // Noel O’Hara 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib")
#pragma comment(lib,"sfml-window-d.lib")
#pragma comment(lib,"sfml-network-d.lib")
#else #pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#include <SFML/Graphics.hpp> 
#include <iostream>

void checkinput();
int pixelsPerMeter = 1;
sf::RenderWindow window(sf::VideoMode(800, 800), "Go Physics!!");
sf::CircleShape shape(5.0f);

sf::Vector2f velocity(0, 0);
sf::Vector2f position(400, 0);
sf::Vector2f jumpOff(0, 50 * pixelsPerMeter);
//9.8f
sf::Vector2f gravity(0.0f, 9.8f * pixelsPerMeter);

const sf::Time timePerFrame = sf::seconds(1.0f / 60.0f);
sf::Time timeSinceLastUpdate = sf::Time::Zero;
sf::Time jumpCoolDown;
sf::VertexArray lineToMouse(sf::LineStrip);
sf::VertexArray ballTrail(sf::LinesStrip);

sf::Vector2f getUnitVector(sf::Vector2f t_vector);

sf::Vector2f getUnitVector(sf::Vector2f t_vector)
{
	
	float magnitude;
	magnitude = sqrt(t_vector.x * t_vector.x)+(t_vector.y * t_vector.y);
	t_vector.x = t_vector.x / magnitude;
	t_vector.y = t_vector.y / magnitude;
	return t_vector;
}

int main()
{ 
	
	sf::Clock myClock;
	const float FPS = 144.0f;
	shape.setFillColor(sf::Color::Green);
	shape.setOrigin(shape.getRadius(), shape.getRadius());
	
	myClock.restart();
	while (window.isOpen()) 
	{
      //read keyboard inout
	sf::Event event;
	while (window.pollEvent(event)) 
	{
		if (event.type == sf::Event::Closed)
		{
			window.close();
		}
		
	} 
	//get the time since last update and restart the clock 
	jumpCoolDown += myClock.getElapsedTime();
	timeSinceLastUpdate += myClock.restart(); 
	


	//update every 60th of a second 
		if (timeSinceLastUpdate > timePerFrame) 
		{ 
			ballTrail.append(shape.getPosition());
			

			
			checkinput();
		


			window.clear();
			float timeChange = (float)timeSinceLastUpdate.asSeconds();
			//update position and velocity
			
			position = position + velocity * (timeChange * shape.getRadius());
			velocity = velocity + gravity * (timeChange * shape.getRadius());
			if (position.y >= 400 || position. y < 0)
			{
				velocity.y = -velocity.y;
				velocity.y *= .9;
			}
			if (position.x >= 800 -  shape.getRadius() * 2 || position.x < 0)
			{
				velocity.x = -velocity.x;
				velocity.x *= .9;
			}
			
			velocity.x *= .99;
			velocity.y *= .99;
			shape.setPosition(position);
			window.draw(shape); 
			window.draw(ballTrail);
			window.draw(lineToMouse);
			lineToMouse.clear();
			window.display(); 
			timeSinceLastUpdate = sf::Time::Zero; 
			
		} 
	} 
	return 0; 
}

void checkinput()
{
	sf::Vector2i mousePos;
	mousePos = sf::Mouse::getPosition(window);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		lineToMouse.append(sf::Vertex(sf::Vector2f(mousePos), sf::Color::White));
		lineToMouse.append(sf::Vertex(shape.getPosition(), sf::Color::Transparent));



		sf::Vector2f vectorBetween = sf::Vector2f(mousePos) - shape.getPosition();
		float lengthOfVector = ((sqrt(vectorBetween.x * vectorBetween.x) + (sqrt(vectorBetween.y * vectorBetween.y))));
		sf::Vector2f mouseToBall;
		mouseToBall.x = ((vectorBetween.x / lengthOfVector) * (lengthOfVector / 20)) * pixelsPerMeter;
		mouseToBall.y = ((vectorBetween.y / lengthOfVector) * (lengthOfVector / 20)) * pixelsPerMeter;

		velocity += mouseToBall;

	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && jumpCoolDown.asSeconds() > 2)
	{
		jumpCoolDown = sf::Time::Zero;
		velocity.y -= jumpOff.y;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		velocity.x -= 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		velocity.x += 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		ballTrail.clear();
	}
}

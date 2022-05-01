
#include "Ray.h"

Ray::Ray(float angle)//constructor takes an angle as arguement for direction
{
	m_dir = sf::Vector2f(1, 1); //initialise variable
	thor::setPolarAngle(m_dir, angle); // sets the angle of dir to passed value, the ray can be considered as a single vector of m_source + m_dir, but it is nice to have them separate
}

void Ray::draw(sf::RenderWindow& t_window)
{
	lines[0] = source;
	lines[0].color = sf::Color::White;
	lines[1].color = sf::Color::White;	
	lines[1] =  intersectionPoint; // this is the same deal as above, we need to translate the endpoint otherwise it will draw from 0,0
	t_window.draw(lines); // only draw while an intersection is true
}

void Ray::storeWall(Boundary& t_wall)
{
	StoredHitWall = &t_wall;
}

void Ray::storeSprite(BillboardedBoundary& t_sprite)
{
	storedSprite = &t_sprite;
}

void Ray::storeEnemy(EnemyOne& t_sprite)
{
	storedEnemy = &t_sprite;
}

Boundary* Ray::getWall()
{
	return StoredHitWall;
}

BillboardedBoundary* Ray::getSprite()
{	
		return storedSprite;	
}

EnemyOne* Ray::getEnemy()
{
	return storedEnemy;
}


//so this is the real meat and bones, it is essentially a line intersection formula, which gives us a boolean value for intersects for drawing, but also gives us the point at which a ray and a barrier intersects,
//from that, we can get the distance between the source of the ray and intersection point and use this to determine how tall the wall should be drawn on our render window
sf::Vector2f Ray::cast(Boundary bound)
{
	const float x1 = bound.startPoint.x;
	const float y1 = bound.startPoint.y;
	const float x2 = bound.endPoint.x;
	const float y2 = bound.endPoint.y;
		   
	const float x3 = this->source.x;
	const float y3 = this->source.y;
	const float x4 = this->source.x + this->m_dir.x;
	const float y4 = this->source.y + this->m_dir.y;

	const float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (den == 0) {
		return sf::Vector2f(INFINITY,INFINITY);
	}

	const float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
	const float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;
	if (t > 0 && t < 1 && u > 0) {
		sf::Vector2f pt;
		pt.x = x1 + t * (x2 - x1);
		pt.y = y1 + t * (y2 - y1);
		textureToRender = bound.texture;
		
		return pt;
	}
	else {
		return sf::Vector2f(INFINITY, INFINITY);
	}
}

sf::Vector2f Ray::castAtSprite(BillboardedBoundary* bound)
{
	const float x1 = bound->startPoint.x;
	const float y1 = bound->startPoint.y;
	const float x2 = bound->endPoint.x;
	const float y2 = bound->endPoint.y;

	const float x3 = this->source.x;
	const float y3 = this->source.y;
	const float x4 = this->source.x + this->m_dir.x;
	const float y4 = this->source.y + this->m_dir.y;

	const float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	if (den == 0) {
		return sf::Vector2f(INFINITY, INFINITY);
	}

	const float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
	const float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;
	if (t > 0 && t < 1 && u > 0) {
		sf::Vector2f pt;
		pt.x = x1 + t * (x2 - x1);
		pt.y = y1 + t * (y2 - y1);
		spriteToRender = bound->texture;
		//storeSprite(*bound);
		return pt;
	}
	else {
		return sf::Vector2f(INFINITY, INFINITY);
	}
}

sf::Vector2f Ray::castAtEnemy(EnemyOne* Enemy)
{
	const float x1 = Enemy->getSprite()->startPoint.x;
	const float y1 = Enemy->getSprite()->startPoint.y;
	const float x2 = Enemy->getSprite()->endPoint.x;
	const float y2 = Enemy->getSprite()->endPoint.y;

	const float x3 = this->source.x;
	const float y3 = this->source.y;
	const float x4 = this->source.x + this->m_dir.x;
	const float y4 = this->source.y + this->m_dir.y;

	const float den = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	
	if (den == 0) {
		return sf::Vector2f(INFINITY, INFINITY);
	}

	const float t = ((x1 - x3) * (y3 - y4) - (y1 - y3) * (x3 - x4)) / den;
	const float u = -((x1 - x2) * (y1 - y3) - (y1 - y2) * (x1 - x3)) / den;
	if (t > 0 && t < 1 && u > 0) {
		sf::Vector2f pt;
		pt.x = x1 + t * (x2 - x1);
		pt.y = y1 + t * (y2 - y1);
		enemyToRender = Enemy->getSprite()->texture;

		return pt;
	}
	else {
		return sf::Vector2f(INFINITY, INFINITY);
	}
}

void Ray::update(sf::RenderWindow& t_window, std::vector<Boundary> bounds)
{
	//cast(bounds); // just a method to call cast for now, might have more functionality in the future	
}


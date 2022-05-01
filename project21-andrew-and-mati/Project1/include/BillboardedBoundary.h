#pragma once
#include "Boundary.h"
#include <Thor/Vectors.hpp>

enum class Type
{

    Billboarded,
    Rotating,
};

class BillboardedBoundary : public Boundary
{
public:
    bool active = true;
    BillboardedBoundary(sf::Vector2f pos, int t_texture, int width)
    {
        Boundary::startPoint = pos - sf::Vector2f(width,0);
        Boundary::endPoint = pos + sf::Vector2f(width,0);
        Boundary::texture = t_texture;
      
        midPoint = sf::Vector2f(pos);
      
        this->rotatable.setSize(sf::Vector2f(thor::length(startPoint - endPoint), 1));
        this->rotatable.setOrigin(rotatable.getGlobalBounds().width / 2, rotatable.getGlobalBounds().height / 2);
        this->rotatable.setRotation(thor::polarAngle(startPoint - endPoint));
        this->rotatable.setFillColor(sf::Color::Magenta);
        this->rotatable.setPosition(midPoint);
        this->spriteType = Type::Billboarded;
    };



    BillboardedBoundary(sf::Vector2f pos, int t_texture, int width, Type t_type)
    {
        Boundary::startPoint = pos - sf::Vector2f(width, 0);
        Boundary::endPoint = pos + sf::Vector2f(width, 0);
        Boundary::texture = t_texture;

        midPoint = sf::Vector2f(pos);

        this->rotatable.setSize(sf::Vector2f(thor::length(startPoint - endPoint), 1));
        this->rotatable.setOrigin(rotatable.getGlobalBounds().width / 2, rotatable.getGlobalBounds().height / 2);
        this->rotatable.setRotation(thor::polarAngle(startPoint - endPoint));
        this->rotatable.setFillColor(sf::Color::Magenta);
        this->rotatable.setPosition(midPoint);
        this->spriteType = t_type;
    };

    BillboardedBoundary()
    {
    };


    Type spriteType;
    sf::Vector2f midPoint;
    sf::RectangleShape rotatable;

    void updatePos(sf::Vector2f t_newPos, int width) 
    {
        this->rotatable.setPosition(t_newPos);
        Boundary::startPoint = t_newPos - sf::Vector2f(width, 0);
        Boundary::endPoint = t_newPos + sf::Vector2f(width, 0);
    }


    void updateV3(sf::Vector2f t_playerPos)
    {
        if (spriteType == Type::Billboarded)
        {
            rotatable.setRotation(thor::polarAngle(t_playerPos - rotatable.getPosition()) + 90);
            this->startPoint = rotatable.getTransform().transformPoint(rotatable.getPoint(0));
            this->endPoint = rotatable.getTransform().transformPoint(rotatable.getPoint(2));
        }
        else if (spriteType == Type::Rotating)
        {
          rotatable.rotate(3);
          this->startPoint = rotatable.getTransform().transformPoint(rotatable.getPoint(0));
          this->endPoint = rotatable.getTransform().transformPoint(rotatable.getPoint(2));
        }
    }
};


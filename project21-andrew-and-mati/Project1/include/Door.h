#pragma once
#include "Boundary.h"
#include "Thor/Vectors.hpp"
#include <iostream>


class Door : public Boundary
{
public:
    Door() {};

    Door(sf::Vector2f t_startP, sf::Vector2f t_endP, int t_texture) 
    {
        Boundary::startPoint = t_startP;
        Boundary::endPoint = t_endP;
        Boundary::texture = t_texture;
    };

    bool isOpen = false;
    float detectionlength = 35.0f;

    void interact()
    {
        if (isOpen == false)
        {
            isOpen = true;
            std::cout << "boundary interacted with" << std::endl;
            sf::Vector2f directionVector = endPoint - startPoint;       

            startPoint.y -= 32.0f;
            endPoint.y -= 32.0f;
        }
    }
};


#pragma once
#include "SpriteObject.h"
class Platform :
    public SpriteObject
{
public:

    Platform(sf::Vector2f newPosition);

private:

    sf::Vector2f position;
};


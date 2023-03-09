#pragma once
#include "SpriteObject.h"
class Door :
    public SpriteObject
{
public: 

    Door();

private:

    sf::Vector2f position;
};


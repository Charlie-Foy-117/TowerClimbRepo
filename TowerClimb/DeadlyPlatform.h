#pragma once
#include "Platform.h"

class LevelScreen;

class DeadlyPlatform :
    public Platform
{
public:

    DeadlyPlatform(sf::Vector2f newPosition, LevelScreen* newLevelScreen);

    void HandleCollision(SpriteObject& other) override;

private:

    LevelScreen* levelScreen;
};


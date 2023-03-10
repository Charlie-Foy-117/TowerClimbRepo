#pragma once
#include "Screen.h"
#include "Player.h"
#include "Door.h"
#include "Platform.h"
#include <SFML/Graphics.hpp>

class LevelScreen :
    public Screen
{
public:

    LevelScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

private:

    Player player;
    Platform platform;
    Door door;
};


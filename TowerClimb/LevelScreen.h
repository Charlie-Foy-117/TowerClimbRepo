#pragma once
#include "Screen.h"
#include "Player.h"
#include "Door.h"
#include <SFML/Graphics.hpp>

class Platform;
class Game;

class LevelScreen :
    public Screen
{
public:

    LevelScreen(Game* newGamePointer);

    void Update(sf::Time frameTime) override;
    void Draw(sf::RenderTarget& target) override;

private:

    std::vector<Platform*> platformVector;
    Player player;
    Door door;
};


#pragma once
#include "Screen.h"
#include "Player.h"
#include "Door.h"
#include "EndPanel.h"
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

    void TriggerEndState(bool win);

private:

    void Restart();

    std::vector<Platform*> platformVector;
    Player player;
    Door door;
    EndPanel endPanel;
    bool gameRunning;
    sf::Window window;

    sf::View camera;
};


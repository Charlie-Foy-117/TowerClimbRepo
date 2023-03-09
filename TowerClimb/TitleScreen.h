#pragma once
#include "Screen.h"
class TitleScreen :
    public Screen
{
public:

    TitleScreen(Game* newGamePointer);

    void Update(sf::Time frameTime);
    void Draw(sf::RenderTarget& target);

};


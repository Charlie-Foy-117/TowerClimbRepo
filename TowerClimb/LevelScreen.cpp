#include "LevelScreen.h"
#include "AssetManager.h"
#include "Platform.h"
#include "MovingPlatform.h"
#include "BreakingPlatform.h"
#include "DeadlyPlatform.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, platformVector()
	, player()
	, door()
{
	player.SetPosition(200, 200);

	platformVector.push_back(new Platform(sf::Vector2f(200, 400)));
	platformVector.push_back(new MovingPlatform(sf::Vector2f(500, 500), sf::Vector2f(500, 500), sf::Vector2f(700, 500)));
	platformVector.push_back(new BreakingPlatform(sf::Vector2f(500, 400)));
	platformVector.push_back(new DeadlyPlatform(sf::Vector2f(700, 400)));


	door.SetPosition(200, 250);
}

void LevelScreen::Update(sf::Time frameTime)
{
	player.Update(frameTime);
	
	for (size_t i = 0; i < platformVector.size(); ++i)
	{
		platformVector[i]->Update(frameTime);
	}

	player.SetColliding(false);

	for (size_t i = 0; i < platformVector.size(); i++)
	{
		platformVector[i]->SetColliding(false);
	}
	door.SetColliding(false);

	for (size_t i = 0; i < platformVector.size(); i++)
	{
		if (platformVector[i]->CheckCollision(player))
		{
			player.SetColliding(true);
			platformVector[i]->SetColliding(true);
			player.HandleCollision(*platformVector[i]);
			platformVector[i]->HandleCollision(player);
		}
	}
	
	if (player.CheckCollision(door))
	{
		player.SetColliding(true);
		door.SetColliding(true);
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	for (size_t i = 0; i < platformVector.size(); i++)
	{
		platformVector[i]->Draw(target);
	}
	door.Draw(target);
	player.Draw(target);
}

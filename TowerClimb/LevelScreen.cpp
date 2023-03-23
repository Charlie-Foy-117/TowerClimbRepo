#include "LevelScreen.h"
#include "AssetManager.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, testPlatform()
	, testMovingPlatform(sf::Vector2f(0, 700), sf::Vector2f(1000, 700))
	, door()
{
	player.SetPosition(200, 200);
	testPlatform.SetPosition(200, 400);
	testMovingPlatform.SetPosition(sf::Vector2f(500, 700));
	door.SetPosition(200, 250);
}

void LevelScreen::Update(sf::Time frameTime)
{
	player.Update(frameTime);
	testMovingPlatform.Update(frameTime);

	player.SetColliding(false);
	testPlatform.SetColliding(false);
	testMovingPlatform.SetColliding(false);
	door.SetColliding(false);

	if (player.CheckCollision(testPlatform))
	{
		player.SetColliding(true);
		testPlatform.SetColliding(true);
		player.HandleCollision(testPlatform);
	}
	if (player.CheckCollision(testMovingPlatform))
	{
		player.SetColliding(true);
		testMovingPlatform.SetColliding(true);
		player.HandleCollision(testMovingPlatform);
	}
	if (player.CheckCollision(door))
	{
		player.SetColliding(true);
		door.SetColliding(true);
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	testPlatform.Draw(target);
	testMovingPlatform.Draw(target);
	door.Draw(target);
	player.Draw(target);
}

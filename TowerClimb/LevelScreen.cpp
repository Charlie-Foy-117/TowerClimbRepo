#include "LevelScreen.h"
#include "AssetManager.h"

LevelScreen::LevelScreen(Game* newGamePointer)
	: Screen(newGamePointer)
	, player()
	, platform()
	, door()
{
	player.SetPosition(500, 500);
	platform.SetPosition(200, 400);
	door.SetPosition(200, 250);
}

void LevelScreen::Update(sf::Time frameTime)
{
	player.Update(frameTime);

	player.SetColliding(false);
	platform.SetColliding(false);
	door.SetColliding(false);

	if (player.CheckCollision(platform))
	{
		player.SetColliding(true);
		platform.SetColliding(true);
		player.HandleCollision(platform);
	}
	if (player.CheckCollision(door))
	{
		player.SetColliding(true);
		door.SetColliding(true);
	}
}

void LevelScreen::Draw(sf::RenderTarget& target)
{
	platform.Draw(target);
	door.Draw(target);
	player.Draw(target);
}

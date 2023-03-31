#include "DeadlyPlatform.h"
#include "AssetManager.h"
#include "LevelScreen.h"

DeadlyPlatform::DeadlyPlatform(sf::Vector2f newPosition, LevelScreen* newLevelScreen)
	: Platform(newPosition)
	, levelScreen(newLevelScreen)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/DeadlyPlatform.png"));
	SetPosition(newPosition);
}

void DeadlyPlatform::HandleCollision(SpriteObject& other)
{
	other.SetAlive(false);
	SpriteObject::HandleCollision(other);
	levelScreen->TriggerEndState(true);
}

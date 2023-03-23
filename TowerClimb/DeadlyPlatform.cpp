#include "DeadlyPlatform.h"
#include "AssetManager.h"

DeadlyPlatform::DeadlyPlatform(sf::Vector2f newPosition)
	: Platform(newPosition)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/DeadlyPlatform.png"));
	SetPosition(newPosition);
}

void DeadlyPlatform::HandleCollision(SpriteObject& other)
{
	other.SetAlive(false);
}
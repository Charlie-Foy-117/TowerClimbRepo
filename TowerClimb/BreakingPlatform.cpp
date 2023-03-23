#include "BreakingPlatform.h"
#include "AssetManager.h"

BreakingPlatform::BreakingPlatform(sf::Vector2f newPosition)
	:Platform(newPosition)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/BreakingPlatform.png"));
	SetPosition(newPosition);
}

void BreakingPlatform::HandleCollision(SpriteObject& other)
{
	alive = false;
}

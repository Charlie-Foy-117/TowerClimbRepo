#include "Platform.h"
#include "AssetManager.h"

Platform::Platform()
	: SpriteObject()
	, position(200, 100)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Platform.png"));

	collisionOffset = sf::Vector2f(0, -57);
	collisionScale = sf::Vector2f(1.0f, 0.25f);
}

#include "Door.h"
#include "AssetManager.h"

Door::Door()
	:SpriteObject()
	, position (300, 400)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Door.png"));
	
	collisionOffset = sf::Vector2f(0, 10);
	collisionScale = sf::Vector2f(0.5f, 0.85f);
}

#include "Door.h"
#include "AssetManager.h"
#include "LevelScreen.h"

Door::Door(LevelScreen* newLevelScreen)
	: SpriteObject()
	, levelScreen(newLevelScreen)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Door.png"));
	
	collisionOffset = sf::Vector2f(0, 10);
	collisionScale = sf::Vector2f(0.5f, 0.85f);
}

void Door::HandleCollision(SpriteObject& other)
{
	levelScreen->TriggerEndState(true);
	SpriteObject::HandleCollision(other);
}

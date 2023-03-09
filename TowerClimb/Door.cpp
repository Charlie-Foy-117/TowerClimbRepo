#include "Door.h"
#include "AssetManager.h"

Door::Door()
	:SpriteObject()
	, position (300, 400)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Door.png"));
	sprite.setPosition(position);
}

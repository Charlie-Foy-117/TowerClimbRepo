#include "Platform.h"
#include "AssetManager.h"

Platform::Platform()
	: SpriteObject()
	, position(200, 100)
{
	sprite.setTexture(AssetManager::RequestTexture("Assets/Graphics/Platform.png"));
	sprite.setPosition(position);
}

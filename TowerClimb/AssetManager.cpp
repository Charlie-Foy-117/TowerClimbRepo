#include "AssetManager.h"

std::map<std::string, sf::Texture> AssetManager::textures;

sf::Texture& AssetManager::RequestTexture(std::string textureName)
{
    // TODO: insert return statement here
    auto pairFound = textures.find(textureName);

	if (pairFound != textures.end())
	{
		//we found an existing texture, use it
		return pairFound->second; //the value in the key-value pair
	}
	else
	{
		sf::Texture& newTexture = textures[textureName];
		newTexture.loadFromFile(textureName);
		return newTexture;
	}
}

sf::Font& AssetManager::RequestFont(std::string assetName)
{
	// TODO: insert return statement here
}

sf::SoundBuffer& AssetManager::RequestSoundBuffer(std::string assetName)
{
	// TODO: insert return statement here
}

void AssetManager::DestroyAllAssets()
{
	textures.clear();
}

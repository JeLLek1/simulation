#include "pch.h"
#include "TextureManager.h"


void TextureManager::loadTexture(const std::string& name, const std::string& filename)
{

	sf::Texture tex;
	tex.loadFromFile(filename);

	this->textures[name] = tex;

	return;

}

sf::Texture& TextureManager::getRef(const std::string& texture)
{
	return this->textures.at(texture);
}

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
}

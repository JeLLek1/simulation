#include "pch.h"
#include "TextureManager.h"


void TextureManager::loadTexture(const TextureNames& texture, const std::string& filename)
{

	sf::Texture* temp = new sf::Texture;
	if (temp->loadFromFile(filename) == false) {
		delete temp;
		//do something
	}
	this->textures.insert(std::pair<TextureNames, sf::Texture*>(texture, temp));

	return;
}

sf::Texture* TextureManager::getRef(const TextureNames& texture)
{
	return this->textures.at(texture);
}

TextureManager::TextureManager()
{
}


TextureManager::~TextureManager()
{
	for (std::map<TextureNames, sf::Texture*>::iterator itr = this->textures.begin(); itr != this->textures.end(); itr++)
	{
		delete (itr->second);
	}
	this->textures.clear();
}

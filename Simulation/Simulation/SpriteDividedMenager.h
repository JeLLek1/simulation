#pragma once
#include <map>
#include <SFML/Graphics.hpp>
#include "TextureManager.h"

class SpriteDivided : public sf::Sprite {
public:
	sf::Vector2u partSize;
	unsigned char partLenght;
};

class SpriteDividedMenager
{
private:
	std::map<TextureNames, SpriteDivided*> sprites;
public:

	void loadSprite(const TextureNames& name, sf::Texture* texture, sf::Vector2u partSize, unsigned char partLenght, bool centerBottom = true);
	SpriteDivided* getRef(const TextureNames& name);

	SpriteDividedMenager();
};


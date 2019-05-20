#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "SpriteDividedMenager.h"
#include "StaticObject.h"
#include <iostream>


class Tile
{
private:
	ObjectType objectType;
	size_t objectListPosition;
	bool collision;
public:
	unsigned char partNumber;
	TextureNames texname;

	Tile();
	Tile(unsigned char partNumber, TextureNames texname, bool collision = false);
	void draw(sf::RenderWindow* window, SpriteDivided* sprite, unsigned int x, unsigned int y, unsigned int mapWidth, float dt);
};


#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "SpriteDividedMenager.h"
#include <iostream>


class Tile
{
public:
	unsigned char partNumber;
	TextureNames texname;
	bool collision;

	Tile();
	Tile(unsigned char partNumber, TextureNames texname, bool collision = false);
	void draw(sf::RenderWindow* window, SpriteDivided* sprite, unsigned int x, unsigned int y, unsigned int mapWidth, float dt);
};


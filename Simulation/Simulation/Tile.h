#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "SpriteDividedMenager.h"
#include "ObjectType.h"
#include <iostream>


class Tile
{
private:
	ObjectType objectType;
	size_t objectListPosition;
	bool collision;
	unsigned char partNumber;
public:

	Tile();
	Tile(unsigned char partNumber, TextureNames texname, bool collision = false);
	void draw(sf::RenderWindow* window, SpriteDivided* sprite, unsigned int x, unsigned int y, unsigned int mapWidth, unsigned int animationStep);
	void setPart(unsigned char partNumber);
	bool returnCollision();
	void setCollision(bool collision);
	ObjectType returnObjectType();
	void setObjectType(ObjectType ObjectType);
};


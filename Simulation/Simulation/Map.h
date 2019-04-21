#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Tile.h"
#include "SpriteDividedMenager.h"
#include "TextureManager.h"
class Map
{
public:
	std::vector<Tile*> titles;
	sf::Vector2u mapSize;
	void load();
	void draw(sf::RenderWindow& window, float dt, sf::Vector2i playerPos, SpriteDividedMenager& spriteMgr);
	Map();
	Map(unsigned int sizex, unsigned int sizey);
};

#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "Tile.h"
#include "SpriteDividedMenager.h"
#include "TextureManager.h"

class Map
{
private:
	std::vector<Tile*> tiles;
	sf::Vector2u mapSize;
public:
	std::vector<Tile*>& getTileReference();
	Tile* returnTile(sf::Vector2u cords);
	unsigned int mapWidth();
	unsigned int mapHeight();
	void load();
	void load(std::vector<Tile*>& tiles);
	void draw(sf::RenderWindow* window, float dt, sf::Vector2f camPosIso, sf::Vector2f camSize, SpriteDividedMenager* spriteMgr);
	size_t cordToTabPos(sf::Vector2u pos);
	Map(sf::Vector2u* mapsize);
	Map(sf::Vector2u* mapsize, std::vector<Tile*>& tiles);
};

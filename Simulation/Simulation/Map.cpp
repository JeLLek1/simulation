#include "pch.h"
#include "Map.h"
#include "Simulation.h"
#include <iostream>
std::vector<Tile*>& Map::getTileReference()
{
	return this->tiles;
}

Tile* Map::returnTile(size_t x, size_t y)
{
	return this->tiles[this->cordToTabPos(sf::Vector2u(x,y))];
}

unsigned int Map::mapWidth()
{
	return this->mapSize.x;
}

unsigned int Map::mapHeight()
{
	return this->mapSize.y;
}

void Map::load()
{
	for (unsigned int x = 0; x < this->mapSize.y*this->mapSize.y; x++) {
		this->tiles.push_back(new Tile(0, TextureNames::GROUND));
	}
}

void Map::load(std::vector<Tile*>& tiles)
{
	for (std::vector< Tile* >::iterator it = this->tiles.begin(); it != this->tiles.end(); ++it)
	{
		delete (*it);
	}
	this->tiles.clear();
	this->tiles = tiles;
}

void Map::draw(sf::RenderWindow* window, float dt, sf::Vector2f camPosIso, sf::Vector2f camSize, SpriteDividedMenager& spriteMgr)
{
	sf::Vector2i begin = sf::Vector2i(Simulation::isoToCart( camPosIso - (camSize * 0.5f), this->mapSize.x));
	sf::Vector2i end = sf::Vector2i(Simulation::isoToCart(camPosIso + (camSize * 0.5f), this->mapSize.x));
	int triangleendX = static_cast<int>((end.x - begin.x) / 2) + 1;
	int miny = end.x - begin.x + begin.y;
	for (int i = 0; i < triangleendX +1; i++) {
		for (int j = -i-2; j < i+3; j++) {
			int x = begin.x + i;
			int y = begin.y + j;
			if (x >= 0 && y >= 0 && x < this->mapSize.x && y < this->mapSize.y ) {
				this->returnTile(x, y)->draw(window, spriteMgr.getRef(TextureNames::GROUND), x, y, this->mapSize.x, spriteMgr.returnAnimationStep());
			}
			x = end.x - i;
			y = end.y - j;
			if (x >= 0 && y >= 0 && x < this->mapSize.x && y < this->mapSize.y && triangleendX != i) {
				this->returnTile(x, y)->draw(window, spriteMgr.getRef(TextureNames::GROUND), x, y, this->mapSize.x, spriteMgr.returnAnimationStep());
			}
		}
	}
}

size_t Map::cordToTabPos(sf::Vector2u pos)
{
	return static_cast<size_t>(pos.x + pos.y*this->mapWidth());
}

Map::Map(sf::Vector2u* mapsize)
{
	this->mapSize = sf::Vector2u(*mapsize);
	this->load();
}

Map::Map(sf::Vector2u* mapsize, std::vector<Tile*>& tiles)
{
	this->mapSize = sf::Vector2u(*mapsize);
	this->load(tiles);
}

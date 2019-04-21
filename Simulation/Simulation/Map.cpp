#include "pch.h"
#include "Map.h"
void Map::load()
{
	for (unsigned int y = 0; y < this->mapSize.x; y++) {
		for (unsigned int x = 0; x < this->mapSize.y; x++) {
			this->titles.push_back(new Tile(0, TextureNames::GRASS));
		}
	}
}

void Map::draw(sf::RenderWindow& window, float dt, sf::Vector2i camPos, SpriteDividedMenager& spriteMgr)
{
	for (unsigned int y = camPos.y - 10; y < camPos.y + 10; y++) {
		for (unsigned int x = camPos.x - 10; x < camPos.x + 10; x++) {
			this->titles[x + y * this->mapSize.x]->draw(window, spriteMgr.getRef(this->titles[x + y * this->mapSize.x]->texname), x, y, this->mapSize.x, dt);
		}
	}
}

Map::Map()
{

}

Map::Map(unsigned int sizex, unsigned int sizey)
{
	this->mapSize.x = sizex;
	this->mapSize.y = sizey;
	this->load();
}
#include "pch.h"
#include "Map.h"
#include "SimulationStateEditor.h"
#include <iostream>
void Map::load()
{
	for (unsigned int y = 0; y < this->mapSize.x; y++) {
		for (unsigned int x = 0; x < this->mapSize.y; x++) {
			this->titles.push_back(new Tile(0, TextureNames::GRASS));
		}
	}
}

void Map::draw(sf::RenderWindow* window, float dt, sf::Vector2f camPosIso, sf::Vector2f camSize, SpriteDividedMenager& spriteMgr)
{
	sf::Vector2i begin = sf::Vector2i(SimulationStateEditor::isoToCart( camPosIso - (camSize * 0.5f), this->mapSize.x));
	sf::Vector2i end = sf::Vector2i(SimulationStateEditor::isoToCart(camPosIso + (camSize * 0.5f), this->mapSize.x));
	int triangleendX = static_cast<int>((end.x - begin.x) / 2) + 1;
	int miny = end.x - begin.x + begin.y;
	for (int i = 0; i < triangleendX +1; i++) {
		for (int j = -i-2; j < i+3; j++) {
			int x = begin.x + i;
			int y = begin.y + j;
			if (x >= 0 && y >= 0 && x < this->mapSize.x && y < this->mapSize.y ) {
				this->titles[x + y * this->mapSize.x]->draw(window, spriteMgr.getRef(this->titles[x + y * this->mapSize.x]->texname), x, y, this->mapSize.x, dt);
			}
			x = end.x - i;
			y = end.y - j;
			if (x >= 0 && y >= 0 && x < this->mapSize.x && y < this->mapSize.y && triangleendX != i) {
				this->titles[x + y * this->mapSize.x]->draw(window, spriteMgr.getRef(this->titles[x + y * this->mapSize.x]->texname), x, y, this->mapSize.x, dt);
			}
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
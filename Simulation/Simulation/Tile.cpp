#include "pch.h"
#include "Tile.h"

Tile::Tile()
{

}

Tile::Tile(unsigned char partNumber, TextureNames texname, bool collision)
{
	this->collision = collision;
	this->texname = texname;
	this->partNumber = partNumber;

}

void Tile::draw(sf::RenderWindow* window, SpriteDivided* sprite, unsigned int x, unsigned int y, unsigned int mapWidth, float dt)
{
	//Ustawienie odpowiedniej kratki spritu
	sprite->setTextureRect(sf::IntRect((this->partNumber % 5) * sprite->partSize.x, static_cast<int>(this->partNumber / 5) * sprite->partSize.y, sprite->partSize.x, sprite->partSize.y));
	//Ustawienei odpowiedniej pozycji na ekranie
	sprite->setPosition((x - y) * sprite->partSize.y + mapWidth * sprite->partSize.y, (x + y) * sprite->partSize.y * 0.5);

	window->draw(*sprite);
}

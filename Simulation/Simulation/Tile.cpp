#include "pch.h"
#include "Tile.h"
#include "Simulation.h"

Tile::Tile()
{

}

Tile::Tile(unsigned char partNumber, TextureNames texname, bool collision)
{
	this->collision = collision;
	this->partNumber = partNumber;
	this->objectType = ObjectType::NONE;
	this->objectListPosition = 0;
	//this->staticObject = NULL;
}

void Tile::draw(sf::RenderWindow* window, SpriteDivided* sprite, unsigned int x, unsigned int y, unsigned int mapWidth, unsigned int animationStep)
{
	//Ustawienie odpowiedniej kratki spritu
	sprite->setTextureRect(sf::IntRect((this->partNumber % 5 + ((this->partNumber > 4) ? animationStep : 0)) * sprite->partSize.x , static_cast<int>(this->partNumber / 5) * sprite->partSize.y, sprite->partSize.x, sprite->partSize.y));
	//Ustawienei odpowiedniej pozycji na ekranie
	sprite->setPosition(Simulation::cartToIso(sf::Vector2f(x, y), mapWidth));
	window->draw(*sprite);
	/*if (this->staticObject) {
		this->staticObject->draw();
	}*/
}

void Tile::setPart(unsigned char partNumber)
{
	this->partNumber = partNumber;
	if (this->partNumber > 4) {
		this->collision = true;
	}
}

bool Tile::returnCollision()
{
	return this->collision;
}

void Tile::setCollision(bool collision)
{
	this->collision = collision;
}

void Tile::setObjectType(ObjectType objectType)
{
	this->objectType = objectType;
}

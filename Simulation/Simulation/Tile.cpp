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

//Rysowanie kafelka w odpowiednim miejscu na ekranie
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

//Ustawianie wycinka tekstury
void Tile::setPart(unsigned char partNumber)
{
	this->partNumber = partNumber;
	if (this->partNumber > 4) {
		this->collision = true;
	}
	else {
		this->collision = false;
	}
}

//Zwraca czy dany punkt jest nie do przejœcia
bool Tile::returnCollision()
{
	return this->collision;
}

//Ustawia kolizje na punkcie
void Tile::setCollision(bool collision)
{
	this->collision = collision;
}

//Zwraca typ obiektu znajduj¹cego siê na danym kafelku
ObjectType Tile::returnObjectType()
{
	return this->objectType;
}

//Ustawia informacjê o typie obiektu typu fireplace, resouce
void Tile::setObjectType(ObjectType objectType)
{
	this->objectType = objectType;
}

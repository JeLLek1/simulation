#include "pch.h"
#include <ctime>
#include <cstdlib>

#include "staticObjectResouces.h"
#include "Simulation.h"

void StaticObjectResouces::draw(sf::RenderWindow* window, SpriteDivided* sprite, unsigned int mapWidth, unsigned int animationStep)
{
	sprite->setTextureRect(sf::IntRect( this->version * sprite->partSize.x, static_cast<int>(this->objectType)* sprite->partSize.y, sprite->partSize.x, sprite->partSize.y));
	//Ustawienei odpowiedniej pozycji na ekranie
	sprite->setPosition(Simulation::cartToIso(sf::Vector2f(this->posiotion.x, this->posiotion.y), mapWidth));
	window->draw(*sprite);
}

void StaticObjectResouces::update(const float dt)
{
}

StaticObjectResouces::StaticObjectResouces(const ObjectType objectType, Map* map) : StaticObject(objectType, map)
{

	sf::Vector2u round;

	do {
		round.x = rand() % map->mapWidth();
		round.y = rand() % map->mapHeight();
	} while (map->returnTile(round)->returnCollision());
	this->posiotion = round;
	map->returnTile(round)->setCollision(true);
	map->returnTile(round)->setObjectType(objectType);

	this->version = rand() % 5;
}

StaticObjectResouces::StaticObjectResouces(const ObjectType objectType, sf::Vector2u* pos) : StaticObject(objectType, pos)
{
	this->version = 0;
}

StaticObjectResouces::~StaticObjectResouces()
{
}

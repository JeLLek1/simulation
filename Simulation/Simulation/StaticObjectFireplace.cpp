#include "pch.h"
#include "StaticObjectFireplace.h"
#include "Simulation.h"
#include <iostream>


void StaticObjectFireplace::draw(sf::RenderWindow* window, SpriteDivided* sprite, unsigned int mapWidth, unsigned int animationStep)
{
	sprite->setTextureRect(sf::IntRect(animationStep * sprite->partSize.x, 0 , sprite->partSize.x, sprite->partSize.y));
	//Ustawienei odpowiedniej pozycji na ekranie
	sprite->setPosition(Simulation::cartToIso(sf::Vector2f(this->posiotion.x, this->posiotion.y), mapWidth));
	window->draw(*sprite);
}

void StaticObjectFireplace::update(const float dt)
{
}

StaticObjectFireplace::StaticObjectFireplace(const ObjectType objectType, Map* map) : StaticObject(objectType, map)
{

	sf::Vector2u round;

	do {
		round.x = (rand() % (map->mapWidth()-2)) + 1;
		round.y = (rand() % (map->mapHeight()-2)) + 1;
	} while (map->returnTile(round)->returnCollision());
	this->posiotion = round;
	map->returnTile(round)->setCollision(true);
	map->returnTile(round)->setObjectType(objectType);
}

StaticObjectFireplace::StaticObjectFireplace(const ObjectType objectType, sf::Vector2u* pos) : StaticObject(objectType, pos)
{

}

StaticObjectFireplace::~StaticObjectFireplace()
{
}

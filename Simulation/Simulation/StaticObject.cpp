#pragma once

#include "pch.h"
#include "StaticObject.h"

void StaticObject::setPos(sf::Vector2u pos, Map* map) {
	map->returnTile(this->posiotion)->setCollision(false);
	this->posiotion = pos;
	map->returnTile(this->posiotion)->setCollision(true);
}

sf::Vector2u StaticObject::getPosition()
{
	return this->posiotion;
}

StaticObject::StaticObject(ObjectType objectType, Map* map)
{
	this->objectType = objectType;
	
	sf::Vector2u round;
	do {
		round.x = rand() % map->mapWidth();
		round.y = rand() % map->mapHeight();
	} while (map->returnTile(round)->returnCollision());
	this->posiotion = round;
	map->returnTile(round)->setCollision(true);
	map->returnTile(round)->setObjectType(objectType);
}

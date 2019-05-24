#pragma once

#include "pch.h"
#include "StaticObject.h"

StaticObject::StaticObject(ObjectType objectType, Map* map)
{
	this->objectType = objectType;
	
	sf::Vector2<size_t> round;
	do {
		round.x = rand() % map->mapWidth();
		round.y = rand() % map->mapHeight();
	} while (map->returnTile(round.x, round.y)->returnCollision());
	this->posiotion = sf::Vector2u(round);
	map->returnTile(round.x, round.y)->setCollision(true);
	map->returnTile(round.x, round.y)->setObjectType(objectType);
}

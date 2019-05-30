#pragma once

#include "pch.h"
#include "StaticObject.h"

void StaticObject::setPos(sf::Vector2u pos, Map* map) {
	map->returnTile(this->posiotion)->setCollision(false);

	map->returnTile(this->posiotion)->setObjectType(ObjectType::NONE);
	this->posiotion = pos;
	map->returnTile(this->posiotion)->setCollision(true);
	map->returnTile(this->posiotion)->setObjectType(this->objectType);
}

sf::Vector2u StaticObject::getPosition()
{
	return this->posiotion;
}

StaticObject::StaticObject(ObjectType objectType, Map* map)
{
	this->objectType = objectType;
}

StaticObject::StaticObject(const ObjectType objectType, sf::Vector2u* pos)
{
	this->objectType = objectType;
	this->posiotion.x = pos->x;
	this->posiotion.y = pos->y;
}
